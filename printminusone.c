
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// opaque data type for numbers
typedef uint32_t num_t;

// opaque data type for bit patterns
typedef uint32_t bit_t;

// opaque data type for indices
typedef uint32_t idx_t;

bit_t bitpattern[] = { 0b11, 0b10, 0b01, 0b00 };
char *bitstrings[] = { "11", "10", "01", "00" };

#define END_OF_INDICES  4

// function to extract the bitpattern index
static idx_t extractbitpatternidx(num_t n);
static idx_t *bitpattern2idx32(num_t n);

// ============================================================================
// main
int main(int argc, char ** argv){
    
    num_t numbers[] = { 1024, 16539, UINT32_MAX, UINT32_MAX+1, 7, 8, 10, 14, 25 };

    const size_t nnum = (sizeof numbers) / (sizeof numbers[0]);

    for(int i = 0; i < nnum; ++i){
        num_t n = numbers[i];
        idx_t *indices = bitpattern2idx32(n);
        if(indices == NULL){
            fprintf(stderr, "failed to allocate indices for n = %u\n", n);
            exit(EXIT_FAILURE);
        }

        // 32 + 1 byte string
        char *bitstr = malloc(33);
        if(bitstr == NULL){
            fprintf(stderr, "malloc() error\n");
            exit(EXIT_FAILURE);
        }

        idx_t *tmp = indices;
        idx_t current = *indices;
        char *str = bitstrings[current];
        do{
            strcat(bitstr, str);
            ++tmp;
            current = *tmp;
            str = bitstrings[current];
        }while(current != END_OF_INDICES);

        printf("%u\t\t0b%s\n", n, bitstr);

        free((void *)bitstr);
        free((void *)indices);
    }

    return 0;
}

// ============================================================================
static idx_t extractbitpatternidx(num_t n){
    idx_t i = 0;
    bit_t ext = bitpattern[i];
    bit_t nandext = n & ext;
    bit_t cmp = (nandext == ext);
    while(!cmp){
        ++i;
        ext = bitpattern[i];
        nandext = n & ext;
        cmp = (nandext == ext);
    }
    return i;
}

// ============================================================================
static idx_t *bitpattern2idx32(num_t n){
    const size_t nbytes = sizeof(idx_t) * 17;

    idx_t *indices = malloc(nbytes);
    if(indices == NULL){
        fprintf(stderr, "malloc() failed to allocate memory for 'indices', nbytes = %zu\n", nbytes);
        return NULL;
    }

    int lstidx = 15;
    for(int i = 0; i < 4; ++i){
        /* loop unrolling for faster implementation */
        int shiftbase = 8 * i;

        int s1 = shiftbase;
        int s2 = shiftbase + 2;
        int s3 = shiftbase + 4;
        int s4 = shiftbase + 6;

        num_t n1 = n >> s1;         // n >> 0
        num_t n2 = n >> s2;         // n >> 2
        num_t n3 = n >> s3;         // n >> 4
        num_t n4 = n >> s4;         // n >> 6

        idx_t i1 = extractbitpatternidx(n1);        // least significant two-bits
        idx_t i2 = extractbitpatternidx(n2);
        idx_t i3 = extractbitpatternidx(n3);
        idx_t i4 = extractbitpatternidx(n4);        // most significant two-bits

        int e1 = lstidx;
        int e2 = lstidx - 1;
        int e3 = lstidx - 2;
        int e4 = lstidx - 3;

        indices[e1] = i1;
        indices[e2] = i2;
        indices[e3] = i3;
        indices[e4] = i4;

        lstidx -= 4;
    }

    // set last element
    indices[16] = END_OF_INDICES;

    return indices;
}
