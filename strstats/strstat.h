
#ifndef STRSTAT_H
#define STRSTAT_H

#include "strbytes.h"

#include <stdio.h>      // for ssize_t
#include <stddef.h>     // for size_t

#define INITIAL_NEL         (size_t) 10
#define CACHE_LINE_BYTES    (size_t) 128


// opaque data type for strings
typedef char * str_t;

// opaque data type for pointer to string
typedef str_t * strptr_t;

// opaque data type for offset within strings
typedef size_t strsize_t;

// opaque data type for pointer to offset
typedef strsize_t * offptr_t;

// https://en.cppreference.com/w/c/experimental/dynamic/getline

// sptr: address of a string object
// oarr: address of initial element of array of offset elements
// sbytes: address of memory location in which to store bytes read
// nel: address of memory location in which to store number of string read
ssize_t readstrings(strptr_t saddr, offptr_t *oaddr, bytes_t *sbytes, strsize_t *noff);

void printstrings(char **straddr, size_t **offaddr, size_t nel);

#endif