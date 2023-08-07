
#ifndef STRSTAT_H
#define STRSTAT_H

#include <stdio.h>      // for EOF
#include <stdlib.h>     // malloc(), free(), ...

// histogram computation
#include "hist.h"

// string manipulation
size_t readstrings(char **straddr, size_t **offaddr, size_t nstr, size_t strbytes);
void printstrings(char **straddr, size_t **offaddr, size_t nel);


#endif