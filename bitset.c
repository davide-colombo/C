
#include <stdio.h>
#include <stdint.h>

typedef uint32_t num_t;

static int ispowerof2(num_t n);
static uint32_t countbits(num_t n);

// ============================================================================
// main
int main(int argc, char **argv){

    int res;
    uint32_t n = 1;
    do{
        res = ispowerof2(n);
        printf("%u is power of two? %s\n", n, (res == 1 ? "Yes" : "No"));
        if(res){
            uint32_t nbitsset = countbits(n-1);
            printf("%u is equal to 2^%u\n", n, nbitsset);
        }
        ++n;
    }while(n < 100);
/*
    int i = 0;
    while(i < 32){
        if(n & 1) printf("i = %d\n", i);
        n >>= 1;
        ++i;
    }
*/
    return 0;
}

// ============================================================================
// ispowerof2
static int ispowerof2(num_t n){
    num_t nminus1 = n - 1;
    num_t notn = ~n;
    num_t nand = (notn & nminus1);
    return (nand == nminus1);
}

// ============================================================================
// countbits
static uint32_t countbits(num_t n){
    uint32_t c;
    for(c = 0; n; ++c)
        n &= n - 1;
    return c;
}
