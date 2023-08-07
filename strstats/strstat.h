
#ifndef STRSTAT_H
#define STRSTAT_H

#include <stddef.h>     // for size_t

size_t readstrings(char **straddr, size_t **offaddr, size_t nstr, size_t strbytes);
void printstrings(char **straddr, size_t **offaddr, size_t nel);

#endif