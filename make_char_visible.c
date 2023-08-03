
#include <stdio.h>
#include <stdint.h>

#define BCKS 0x0008
#define HTAB 0x0009
#define BSLH 0x005C

#define NULL_CHAR '\0'

int main(){

    int32_t c;

    while((c = getchar()) != EOF){
        uint32_t bslh_mask = (uint32_t) ((int32_t) ((c == BSLH) << 31) >> 31);
        uint32_t htab_mask = (uint32_t) ((int32_t) ((c == HTAB) << 31) >> 31);
        uint32_t bcks_mask = (uint32_t) ((int32_t) ((c == BCKS) << 31) >> 31);

        uint32_t c1 = (bslh_mask & '\\') | (~bslh_mask & c);
        uint32_t c2 = (htab_mask & '\\') | (~htab_mask & c1);
        uint32_t c3 = (bcks_mask & '\\') | (~bcks_mask & c2);

        putchar(c3);

        uint32_t c4 = (bslh_mask & '\\') | (~bslh_mask & NULL_CHAR);
        uint32_t c5 = (htab_mask & 't') | (~htab_mask & c4);
        uint32_t c6 = (bcks_mask & 'b') | (~bcks_mask & c5);

        putchar(c6);
    }

    return 0;
}