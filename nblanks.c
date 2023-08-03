
#include <stdio.h>
#include <stdint.h>

#define HTAB 0x0009     // 0000 1001
#define NEWL 0x000A     // 0000 1010
#define SPCE 0x0020      // 0010 0000

int main(){

    int32_t c;
    uint32_t cmp;

    uint64_t nl, nt, ns;
    nl = nt = ns = 0;
    do{
        c = getchar();

        nl += (c == NEWL);
        ns += (c == SPCE);
        nt += (c == HTAB);

    } while(c != EOF);
    
    // Make the two ADD instructions independent
    uint64_t nchars_1 = nl + ns;
    uint64_t nchars = nchars_1 + nt;

    printf("nchars = %llu\n", nchars);
    return 0;
}
