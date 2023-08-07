
#ifndef STRSTAT_H
#define STRSTAT_H

#include <stdio.h>
#include <stddef.h>     // for ssize_t

#define INITIAL_NEL         (size_t) 10
#define CACHE_LINE_BYTES    (size_t) 128
#define CACHE_LINE_ELEMS(e) ( (CACHE_LINE_BYTES) / (sizeof (e)) )

// https://en.cppreference.com/w/c/experimental/dynamic/getline
ssize_t readstrings(char **straddr, size_t **offaddr, size_t *strbytes, size_t *n);
void printstrings(char **straddr, size_t **offaddr, size_t nel);

#endif