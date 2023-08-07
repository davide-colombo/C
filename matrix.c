// Davide Colombo
// Monday, 7 August

// ============================================================================

// This program wants to inspect the layout in memory of global
// multi-dimensional arrays.

// First, the address of the array is aligned to a page boundary.

// Second, the rows and columns are allocated as a contiguous
// unique array, not as an array of pointer-to arrays, which
// would be respectively the "rows" and "columns".

// ============================================================================

#include <stdio.h>

#define NROWS   2048u
#define NCOLS   2048u

int matrix[NROWS][NCOLS];

int main(int argc, char **argv){

    printf("sizeof matrix = %zu\n", sizeof matrix);
    int (*crow)[NCOLS] = matrix;
    int (*erow)[NCOLS] = matrix+NROWS;
    do{
        printf("curr row = %p\n", crow);
        //printf("sizeof row = %zu\n", sizeof *crow);
        //printf("sizeof row / sizeof el = %zu\n", sizeof *crow / sizeof *crow[0]);
        ++crow;
    }while( (erow - crow) > 0);

    return 0;
}
