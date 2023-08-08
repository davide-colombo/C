
// project header files
#include "strstat.h"
#include "hist.h"

// standard library header files
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv){

    // contiguous chunk of memory
    char *strings = NULL;

    // array of offsets
    size_t *offsets = NULL;

    // number of allocated elements
    size_t nel = 0UL;
    size_t strbytes = 0UL;

    // read strings from stdin
    ssize_t nstrings = readstrings(&strings, &offsets, &strbytes, &nel);

    // bad practice, need to handle properly
    if(nstrings == -1){
        fprintf(stderr, "Failed to read strings from standard input\n");
        exit(EXIT_FAILURE);
    }

    // How many strings read
    // printf("nstrings = %zu\n", nstrings);

    // print all the strings
    // printstrings(&strings, &offsets, nstrings);

    // pointer to memory location that will holds the histograms of each string
    // Each histogram is a collection of histogram elements, one per unique
    // character found in the string
    // (sort of "offsets" array above for strings)
    size_t *nchperstr = NULL;

    // array of histograms for each string
    // (handled in the same fashion as "strings" array above)
    histelem_t *hists = NULL;

    // free memory
    if(strings != NULL)
        free((void *)strings);

    if(offsets != NULL)
        free((void *)offsets);
    
    if(nchperstr != NULL)
        free((void *)nchperstr);

    return 0;
}