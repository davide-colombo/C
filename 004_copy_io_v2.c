
#include <stdio.h>

main(){

    int c;

    while((c = getchar()) != EOF){
        putchar(c);
        printf("%d (%c) == EOF? %d\n", c, c, (c == EOF));
    }

    /* if we break the while loop, it is because of 'c == EOF' */
    printf("%d (%c) == EOF? %d\n", c, c, (c == EOF));
}