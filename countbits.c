
#include <stdio.h>
#include <stdint.h>

static uint32_t cntbits1(uint32_t v, uint32_t *niteraddress);
static uint32_t cntbits2(uint32_t v, uint32_t *niteraddress);

uint32_t testarray[] = { 128, 65, 34, 21, 16, 13, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

int main(int argc, char **argv){
    uint32_t niter1, niter2;
    int n = sizeof testarray / sizeof testarray[0];
    for(int i = 0; i < n; ++i){
        printf("\n<ITERATION %d>\n", i);
        uint32_t v = testarray[i];
        uint32_t c1 = cntbits1(v, &niter1);
        uint32_t c2 = cntbits2(v, &niter2);
        printf("[cntbits1] v = %u\t c = %u\tniter = %u\n", v, c1, niter1);
        printf("[cntbits2] v = %u\t c = %u\tniter = %u\n", v, c2, niter2);
    }
    return 0;
}

// cntbits1
static uint32_t cntbits1(uint32_t v, uint32_t *niteraddress){
    uint32_t c;
    uint32_t niter;
    for(niter = 0, c = 0; v; v >>= 1, ++niter)
        c += v & 1u;
    *niteraddress = niter;
    return c;
}

// cntbits2
static uint32_t cntbits2(uint32_t v, uint32_t *niteraddress){
    uint32_t c;
    uint32_t niter;
    for(niter = 0, c = 0; v; ++c, ++niter)
        v &= v - 1;
    *niteraddress = niter;
    return c;
}
