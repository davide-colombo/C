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
#include "strbytes.h"               // bytes manipulation

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
ssize_t readstrings(strptr_t saddr, offptr_t *oaddr, bytes_t *sbytes, strsize_t *noff){

    bytes_t alloc_sbytes = *sbytes;
    str_t s = *saddr;
    if( s == NULL ){
        s = malloc(CACHE_LINE_BYTES);
        if( s == NULL ){
            perror("strstat.c: readstrings - failed to allocate memory for 'strs'");
            return -1;
        }
        alloc_sbytes = CACHE_LINE_BYTES;
    }
    
    strsize_t alloc_noff = *noff;
    offptr_t o = *oaddr;
    if( o == NULL ){
        o = calloc(INITIAL_NEL, sizeof(strsize_t));
        if( o == NULL ){
            perror("strstat.c: readstrings - failed to allocate memory for 'offs'");
            return -1;
        }
        alloc_noff = INITIAL_NEL;
    }

    // start reading strings
    register int eof_reached = 0;

    register size_t strs_read = 0;
    register bytes_t bytes_read = 0;

    register offptr_t offbuf = &o[1];              // &offs[0] must be 0
    register str_t readbuf = &s[0];
    register int c;
    do{
        // string array realloc
        if(bytes_read >= (alloc_sbytes-1)){
            bytes_t newbytes = alloc_sbytes * 2;
            if(alloc_sbytes > newbytes){
                // unsigned overflow
                perror("strstat.c: readstrings - failed to double 'alloc_sbytes'");
                return -1;
            }

            // realloc
            char *realloc_sbuf = realloc(s, newbytes);
            if(realloc_sbuf == NULL){
                perror("strstat.c: readstrings - failed to realloc 's'");
                return -1;
            }
            
            // update pointer location
            alloc_sbytes = newbytes;
            s = realloc_sbuf;
            readbuf = realloc_sbuf + bytes_read;
        }

        // offset array realloc
        // NOTE: if realloc expands the same array, memory content
        //          of the new area is undefined
        if(strs_read >= (alloc_noff-1)){
            strsize_t newnel = alloc_noff * 2;
            if(alloc_noff > newnel){
                // unsigned overflow
                perror("strstat.c: readstrings - failed to double 'alloc_noff'");
                return -1;
            }

            // realloc
            offptr_t realloc_obuf = realloc(o, sizeof(strsize_t) * newnel);
            if(realloc_obuf == NULL){
                perror("strstat.c: readstrings - failed to realloc 'offs'");
                return -1;
            }

            // update pointer location
            alloc_noff = newnel;
            o = realloc_obuf;
            offbuf = realloc_obuf + strs_read;
        }

        // read next character
        c = getchar();

        if(c == EOF){
            c = '\0';
            eof_reached = 1;
        }

        *readbuf = c;
        ++readbuf;
        ++bytes_read;                       // one byte successfully read

        if(c == '\n'){
            // NOTE: using local pointers to dynamically-allocated arrays
            // gives the compiler more freedom to optimize because
            // instructions are now independent
            // Furthermore, the processor can decide to schedule ops
            // out-of-order

            ++bytes_read;                   // move the string pointer to the next empty spot
            ++strs_read;                    // increment the counter of "number-of-strings" read

            // update strings array
            *readbuf = '\0';
            ++readbuf;

            // update offset array
            *offbuf = bytes_read;
            ++offbuf;
        }
    }while(!eof_reached);

    // get the position of the bit of the cache line size
    // Cache line size must be a power of two (typically 64 or 128 bytes)
    // Given 64 0b0100 0000, if we subtract 1 we obtain 0b0011 1111
    // And if we count the number of bits in 63 (i.e., 6) we know that
    //      the 'cache line size' is 64 bytes

    const cntbit_t nbitscacheline = countbits(CACHE_LINE_BYTES-1);

    // shrink to precise size array of strings
    if(bytes_read < alloc_sbytes){
        bytes_read = smallpow2raisedb(bytes_read, nbitscacheline) + CACHE_LINE_BYTES;
        char *realloc_sbuf_shrink = realloc(s, bytes_read);
        if(realloc_sbuf_shrink == NULL){
            perror("strstat.c: readstrings - failed to shrink memory for 'strs'");
            return -1;
        }
        // update pointer to location
        s = realloc_sbuf_shrink;
    }

    // shrink to precise size array of offsets
    if(strs_read < alloc_noff){
        bytes_t noffbytes = smallpow2raisedb(strs_read * sizeof(size_t), nbitscacheline) + CACHE_LINE_BYTES;
        offptr_t realloc_obuf_shrink = realloc(o, noffbytes);
        if(realloc_obuf_shrink == NULL){
            perror("strstat.c: readstrings - failed to shrink memory for 'offs'");
            return -1;
        }
        // update pointer location
        o = realloc_obuf_shrink;
    }

    // Store output
    *saddr = s;
    *oaddr = o;
    *noff = strs_read;
    *sbytes = bytes_read;

    return strs_read;
}

// ============================================================================
// printstrings
void printstrings(char **straddr, size_t **offaddr, size_t nel){
    register char *basestr = *straddr;
    register size_t *offptr = *offaddr;
    while(nel){
        size_t off = *offptr;
        puts(basestr + off);
        ++offptr;
        --nel;
    }
}
