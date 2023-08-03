
#include <stdio.h>
#include <stdint.h>

#define BCKS 0x0008
#define HTAB 0x0009
#define BSLH 0x005C

int main(){

    int32_t c;

    do{
        c = getchar();
        uint32_t bcks_mask = (uint32_t) ((int32_t) ((c == HTAB) << 31) >> 31);
        uint32_t new_c = (bcks_mask & '\\') | (~bcks_mask & c);
        putchar(new_c);
    }while(c != EOF);

    return 0;
}