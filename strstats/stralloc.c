
#include "stralloc.h"
#include <stdlib.h>                 // for malloc(), ...
#include <stdio.h>                  // for perror(), ...

// ============================================================================
char *stralloc(size_t nchars){
    // by the Standard, the programmer needs to handle any call to malloc(0)
    if(!nchars){
        perror("stralloc.c: stralloc - cannot allocate 0 byte memory");
        return NULL;
    }

    char *str = malloc(nchars);
    if(str == NULL){
        perror("stralloc.c: stralloc - failed to allocate memory for string");
        return NULL;
    }

    return str;
}

// ============================================================================
size_t *offalloc(size_t nel){
    if(!nel){
        perror("stralloc.c: offalloc - cannot allocate 0 byte memory");
        return NULL;
    }

    size_t *off = malloc(sizeof(*off) * nel);
    if(off == NULL){
        perror("stralloc.c: offalloc - failed to allocate memory for offset");
        return NULL;
    }

    return off;
}