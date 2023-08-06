/*
 * Author:     Davide Colombo
 * Date:       Sunday, 6 August 2023
 * 
 * ////////////////////////////////////////////////////////////////////////////
 * 
 * This program computes the histogram of a set of strings.
 * 
 * ////////////////////////////////////////////////////////////////////////////
 * 
 * There are two ways to store strings:
 * 
 * 1: allocate a contiguous block of memory which size is equal to
 *      the total size of all the strings.
 * 
 *      This may have some drawbacks depending on the size of each
 *      string and the number of strings that we except to read.
 * 
 *      The longer the string the more difficult it is to find a
 *      contiguous chunk of memory.
 * 
 *      Having more strings leads to similar consequences.
 * 
 * 2: allocate an array of pointers to string (i.e. char pointers)
 *
 *      If a pointer occupies 8 bytes (64 bits), the total size of
 *      the array will be equal to 8 bytes x number-of-strings.
 * 
 *      The difference is that each string may be scattered through
 *      memory.
 * 
 *      This can have some drawbacks if we need to load and process
 *      the strings all together, and may result into a higher
 *      cache-miss rate.
 * 
 * Solution 1 treats all strings as a big string.
 * Each string has its own length as usual but they are contiguous in memory.
 * 
 * This is the idea:
 * 
 *      |   str1    |   str2    |   str3    |
 * 
 * Three strings stored one after the other.
 * 
 * This solution improves locality and it is better if we need to manipulate
 * strings all together.
 * 
 * However, we must pay attention to memory allocation.
 * For example, we can allocate a large portion of memory immediately
 * in order to reduce the number of reallocations.
 * 
 * Solution 2 treats strings as isolate chunk of memory.
 * 
 *      |   ptr1    |   ptr2    |   ptr3    |
 *           |           |           |
 *         |str1|     |str2|       |str3|
 * 
 * Only pointers are contiguous, the strings may be scattered throughout memory.
 * 
 * ALIGNMENT:
 * 
 * One important consideration is to allocate memory aligned to cache line
 *      boundary.
 * 
 * ////////////////////////////////////////////////////////////////////////////
 * 
 * Storing histograms of strings
 * 
 * 8 bytes for each character is large enough.
 * 
 * A string may contain 128 different characters.
 * 
 * The ASCII code comprises 128 characters of which 95 are printable.
 * (https://en.cppreference.com/w/cpp/language/ascii)
 * 
 * We consider only strings with printable ASCII characters, therefore
 *      at most, to compute the histogram of one string, we need 
 *      95 bytes.
 * 
 * Depending of the size of the cache line this may fit into one or more lines.
 * 
 * CHARACTER ENCODING:
 * 
 * We can allocate an array of 95 elements for the histogram of one string.
 * 
 * This is straightforward but may be wasteful.
 * 
 * In the extreme case in which one string is made of one char, we are wasting:
 * 
 *                   (95 - 1) / 95 = 98.94% of storage
 * 
 * One solution can be to use the most-significant 7 bits of the 8 bytes
 *      used to encode a histogram entry for a single character.
 * 
 * The remaining bits to count the frequency of the character.
 * 
 *          |63        57|56                       0|
 * 
 * This should be sufficient to accomodate different usages.
 * 
 * ////////////////////////////////////////////////////////////////////////////
 * 
 * How to get strings and histograms at the same time
 * 
 * 
 * Strings are stored at a contiguous block of memory.
 * We keep the base address.
 * 
 * Each string respects the "NULL-TERMINATED BYTE STRING" model.
 * 
 * We keep track of each string using another array of "offsets".
 * 
 * Each entry is a "size_t" type (i.e., 8 bytes on most 64-bit archs).
 * We keep the base address of this array, too.
 * 
 * To retrieve a string we can use a index variable into the array.
 * 
 * When adding a string, it is useful to update this array so that,
 *      the next tentatives to retrieve the specific string can just
 *      take the base address of the block of memory of all strings
 *      and simply add the "offset" for the string "i" in the list.
 * 
 * In other words, when inserting a string we need to insert an entry
 *      into the "offset" array by taking the sum of the previous
 *      entry and adding the length of the inserted string.
 * 
 * ////////////////////////////////////////////////////////////////////////////
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define CACHE_LINE_BYTES    (size_t) 128
#define CACHE_LINE_ELEMS(e) ( (CACHE_LINE_BYTES) / (sizeof (e)) )

#define OFFSETS_INITIAL_NEL     (size_t) 10
#define STRINGS_INITIAL_NEL     (size_t) 10

typedef struct _histelem {
    size_t count: 56, ch: 8;
} histelem;

// ============================================================================
// main
int main(int argc, char **argv){

    // contiguous chunk of memory
    char *strings = NULL;
    strings = malloc(CACHE_LINE_BYTES * STRINGS_INITIAL_NEL);
    if(strings == NULL){
        perror("strstat.c: main - failed to allocate memory for 'strings'");
        exit(EXIT_FAILURE);
    }

    // array of offsets
    size_t nstrings = 0;
    size_t *offsets = NULL;
    offsets = malloc(sizeof(size_t) * OFFSETS_INITIAL_NEL);
    if(offsets == NULL){
        perror("strstat.c: main - failed to allocate memory for 'offsets'");
        exit(EXIT_FAILURE);
    }



    // free memory
    if(strings != NULL)
        free((void *)strings);

    if(offsets != NULL)
        free((void *)offsets);

    return 0;
}
