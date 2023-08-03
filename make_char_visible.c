
#include <stdio.h>
#include <stdint.h>

#define BCKS 0x0008
#define HTAB 0x0009
#define NEWL 0x000A
#define BSLH 0x005C

#define NULL_CHAR '\0'

int main(){

    int32_t c;

    while((c = getchar()) != EOF){
        uint32_t bslh_mask = (uint32_t) ((int32_t) ((c == BSLH) << 31) >> 31);
        uint32_t htab_mask = (uint32_t) ((int32_t) ((c == HTAB) << 31) >> 31);
        uint32_t bcks_mask = (uint32_t) ((int32_t) ((c == BCKS) << 31) >> 31);
        uint32_t newl_mask = (uint32_t) ((int32_t) ((c == NEWL) << 31) >> 31);

        uint32_t c1 = (bslh_mask & '\\') | (~bslh_mask & c);
        uint32_t c2 = (htab_mask & '\\') | (~htab_mask & c1);
        uint32_t c3 = (bcks_mask & '\\') | (~bcks_mask & c2);
        uint32_t c4 = (newl_mask & '\\') | (~newl_mask & c3);

        putchar(c4);

        uint32_t c5 = (bslh_mask & '\\') | (~bslh_mask & NULL_CHAR);
        uint32_t c6 = (htab_mask & 't') | (~htab_mask & c5);
        uint32_t c7 = (bcks_mask & 'b') | (~bcks_mask & c6);
        uint32_t c8 = (newl_mask & 'n') | (~newl_mask & c7);

        putchar(c8);
    }

    return 0;
}