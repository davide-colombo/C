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
 * At most, to compute the histogram of one string, we need 128 bytes.
 * Depending of the size of the cache line this may be two or one lines.
 * 
 * CHARACTER ENCODING:
 * 
 * We can allocate an array of 128 elements for the histogram of one string.
 * 
 * This is straightforward but may be wasteful.
 * 
 * In the extreme case in which one string is made of one char, we are wasting:
 * 
 *                   (128 - 8) / 128 = 93.75% of storage
 * 
 * This way we cannot use the char to index into the array (char are ints).
 * 
 * One solution can be to create a global character table and store its
 *      base address.
 * 
 * Then, use the most-significative 7 bits (2^7 = 128) to get the character
 *      encoding.
 * 
 * The remaining to count the frequency of the character.
 * 
 *          |63        57|56                       0|
 * 
 * This should be sufficient to accomodate different usages.
 * 
 * ////////////////////////////////////////////////////////////////////////////
 * 
 */

#include <stdio.h>


int main(int argc, char **argv){

    return 0;
}
