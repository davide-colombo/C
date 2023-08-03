
#include <stdio.h>
#include <stdint.h>

#define SPCE        (uint32_t) 0x00000020
#define HTAB        (uint32_t) 0x00000009
#define NEWL        (uint32_t) 0x0000000A

#define IN_WORD     (uint32_t) 0xFFFFFFFF
#define OUT_WORD    (uint32_t) 0x00000000

int main(){

    int32_t c;
    uint32_t st;
    uint64_t nw;

    nw = 0;
    st = OUT_WORD;
    while((c = getchar()) != EOF){

        uint32_t spce_mask = (uint32_t) ((int32_t) ((c == SPCE) << 31) >> 31);
        uint32_t newl_mask = (uint32_t) ((int32_t) ((c == NEWL) << 31) >> 31);
        uint32_t htab_mask = (uint32_t) ((int32_t) ((c == HTAB) << 31) >> 31);

        uint32_t not_space = (~spce_mask & ~newl_mask & ~htab_mask);
        uint32_t is_space = (spce_mask | newl_mask | htab_mask);

        uint32_t switch_in = (~st & not_space);
        uint32_t switch_out = (st & is_space);

        uint32_t st1 = (switch_in & IN_WORD) | (~switch_in & st);
        st = (switch_out & OUT_WORD) | (~switch_out & st1);

        // increment
        uint32_t nw1 = nw + 1;
        nw = (switch_in & nw1) | (~switch_in & nw);
    }

    printf("nwords = %llu\n", nw);
    return 0;
}