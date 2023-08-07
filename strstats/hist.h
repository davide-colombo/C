
#ifndef STRSTAT_HIST_H
#define STRSTAT_HIST_H

#include <stddef.h>             // for size_t

typedef struct _histelem {
    size_t count: 56, ch: 8;
} histelem;

// functions for manipulating histograms


#endif