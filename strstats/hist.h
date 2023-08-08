
#ifndef STRSTAT_HIST_H
#define STRSTAT_HIST_H

#include <stddef.h>             // for size_t

// histogram element
// stores a character and its absolute frequency of occurrence in a string
typedef struct histelem {
    size_t count: 56, ch: 8;
} histelem_t;


#endif