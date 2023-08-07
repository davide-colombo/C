
#include <stdio.h>
#include "strstat.h"

#define INITIAL_NEL         (size_t) 10
#define CACHE_LINE_BYTES    (size_t) 128
#define CACHE_LINE_ELEMS(e) ( (CACHE_LINE_BYTES) / (sizeof (e)) )

int main(int argc, char **argv){

    // contiguous chunk of memory
    char *strings = NULL;

    // array of offsets
    size_t *offsets = NULL;

    // read strings from some stream of data
    size_t nstrings = readstrings(&strings, &offsets, INITIAL_NEL, CACHE_LINE_BYTES);
    printf("nstrings = %zu\n", nstrings);

    // print all the strings
    printstrings(&strings, &offsets, nstrings);

    // pointer to memory location that will holds the histograms of each string
    // Each histogram is a collection of histogram elements, one per unique
    // character found in the string
    // (sort of "offsets" array above for strings)
    size_t *nchperstr = NULL;

    // array of histograms for each string
    // (handled in the same fashion as "strings" array above)
    histelem *hists = NULL;

    // free memory
    if(strings != NULL)
        free((void *)strings);

    if(offsets != NULL)
        free((void *)offsets);
    
    if(nchperstr != NULL)
        free((void *)nchperstr);

    return 0;
}