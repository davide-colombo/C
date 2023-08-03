
#include <stdio.h>
#include <stdint.h>

#define SPCE 0x0020
#define HTAB 0x0009
#define NEWL 0x000A

int main(){

    int32_t c;
    while((c = getchar()) != EOF){
        putchar(c);
    }

    return 0;
}