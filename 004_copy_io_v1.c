
#include <stdio.h>

main(){

    int c;      /* 32 bits */

    while((c = getchar()) != EOF)
        printf("c == EOF? %d\n", c == EOF);
        putchar(c);
}