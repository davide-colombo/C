
#include <stdio.h>

#define NEWLINE 10

main(){

    int c, nlines;

    nlines = 0;
    while((c = getchar()) != EOF){
        if(c == NEWLINE){
            ++nlines;
        }
    }
    printf("The total number of lines is %d\n", nlines);
}