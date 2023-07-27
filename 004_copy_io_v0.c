
#include <stdio.h>

main(){

    int c;

    c = getchar();
    while(c != EOF){
        putchar(c);             /* print the current char */
        c = getchar();          /* get the next char */
    }
}