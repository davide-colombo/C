
#ifndef STRSTAT_H
#define STRSTAT_H

#include <stdio.h>      // for ssize_t
#include <stddef.h>     // for size_t

#define INITIAL_NEL         (size_t) 10
#define CACHE_LINE_BYTES    (size_t) 128
#define CACHE_LINE_BITS     7
#define NSHIFTSPOS(bytes)   (size_t)( (((size_t)bytes) >> CACHE_LINE_BITS) )        // bytes / CACHE_LINE_SIZE
#define CEIL_TO_CLSIZE(bytes) ( NSHIFTSPOS((bytes)) << CACHE_LINE_BITS )            // (bytes / CACHE_LINE_SIZE) * CACHE_LINE_SIZE

#define CACHE_LINE_ELEMS(e) ( (CACHE_LINE_BYTES) / (sizeof (e)) )

// https://en.cppreference.com/w/c/experimental/dynamic/getline
ssize_t readstrings(char **straddr, size_t **offaddr, size_t *strbytes, size_t *n);
void printstrings(char **straddr, size_t **offaddr, size_t nel);

#endif