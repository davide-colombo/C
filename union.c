
#include <stdio.h>
#include <stdint.h>

typedef union {
    uint32_t u32;           // 32 bit integer, unsigned
    uint16_t u16[2];        // 2 16 bit integers, unsigned
} u32_t;


int main(int argc, char **argv){
    u32_t in;
    uint16_t lo;
    uint16_t hi;

    in.u32 = 44;
    printf("before swap = %u\n", in.u32);
    
    hi = in.u16[0];
    lo = in.u16[1];
    in.u16[0] = lo;
    in.u16[1] = hi;
    printf("after swap = %u\n", in.u32);

    return 0;
}