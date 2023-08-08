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

// project header files
#include "strstat.h"                // string manipulation

// standard library header files
#include <stdlib.h>                 // malloc(), free(), ...
#include <stddef.h>                 // for size_t

// ============================================================================
// readstrings
// takes the address of the pointer to the memory location where strings are
//      stored by the "caller".
// takes the address of the pointer to the memory location where offsets are
//      stored by the "caller".
// returns the number of strings read or -1 on error
ssize_t readstrings(char **straddr, size_t **offaddr, size_t *strbytes, size_t *n){
    // strings
    char *strs = *straddr;
    if(*straddr == NULL){
        // allocate array
        *strbytes = CACHE_LINE_BYTES;
        strs = malloc(CACHE_LINE_BYTES);
        if(strs == NULL){
            perror("strstat.c: readstrings - failed to allocate memory for 'strs'");
            return -1;
        }
    }
    
    // offsets
    // if '*offaddr' is NOT-NULL and the memory is not set to 0
    // the behavior is UNDEFINED
    size_t *offs = *offaddr;
    if(*offaddr == NULL){

        // safer to call 'calloc' because these are counters
        *n = INITIAL_NEL;
        offs = calloc(INITIAL_NEL, sizeof(size_t));
        if(offs == NULL){
            perror("strstat.c: readstrings - failed to allocate memory for 'offs'");
            return -1;
        }
    }

    // number of strings successfully read
    size_t nstrs = 0;

    // start reading strings
    register int c;
    register char *tmpstr = strs;
    register size_t *tmpoff = &offs[1];
    register size_t eloff = 0;
    register int eof_reached = 0;
    do{
        c = getchar();

        if(c == EOF){
            c = '\0';
            eof_reached = 1;
        }

        ++eloff;                    // increment offset
        *tmpstr = c;                // store the character
        ++tmpstr;

        if(c == '\n'){
            // update strings array
            *tmpstr = '\0';         // finished to read this string
            ++tmpstr;               // move the string pointer to the next empty spot
            
            // update offsets array
            ++eloff;                // one character more because of the '\0'
            *tmpoff = eloff;        // store offset for the current string

            ++tmpoff;               // move to the offset for the next string
            eloff = 0;              // initialize counter to previous value

            ++nstrs;                // increment the counter of "number-of-strings" read
        }
    }while(!eof_reached);

    // assign the arrays
    *straddr = strs;
    *offaddr = offs;
    return nstrs;
}

// ============================================================================
// printstrings
void printstrings(char **straddr, size_t **offaddr, size_t nel){

    // base address
    register char *strptr = *straddr;
    register size_t *offptr = *offaddr;
    
    // IMPORTANT: postfix decrement is a must, otherwise if "nel = 0" it would
    //      SIZE_MAX that is a huge positive integer
    while(nel--){
        strptr += (*offptr);    // point to the next string
        puts(strptr);           // print the current string
        ++offptr;               // get the next offset
    }
}
