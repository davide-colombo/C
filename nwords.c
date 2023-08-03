
#include <stdio.h>
#include <stdint.h>

#define SPCE 0x0020
#define HTAB 0x0009
#define NEWL 0x000A

#define IN 1
#define OUT 0

int main(){

    int32_t c;
    uint32_t st;
    uint64_t nw;

    nw = 0;
    st = OUT;
    while((c = getchar()) != EOF){
        uint32_t not_space = ((c != SPCE) && (c != NEWL) && (c != HTAB));
        uint32_t is_space = ((c == SPCE) || (c == NEWL) || (c == HTAB)); 

        uint32_t st_in = (st == IN);
        uint32_t st_out = (st == OUT);

        uint32_t switch_in = (st_out && not_space);
        uint32_t switch_out = (st_in && is_space);

        uint32_t st1 = (switch_in && IN) || (!switch_in && st);
        st = (switch_out && OUT) || (!switch_out && st1);

        nw += switch_in;
    }

    printf("nwords = %llu\n", nw);
    return 0;
}