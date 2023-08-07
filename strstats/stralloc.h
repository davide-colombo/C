
#ifndef STRALLOC_H_INCLUDED
#define STRALLOC_H_INCLUDED

#include <stddef.h>             // for size_t

char *stralloc(size_t nchars);
size_t *offalloc(size_t nel);

#endif