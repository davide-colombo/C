
#include <stdio.h>

#define NEWLINE 10

int main(){

    int nlines = 0;
    int c;
    do{
        c = getchar();
        if(c == NEWLINE) nlines = nlines + 1;
    } while(c != EOF);

    printf("The total number of lines is %d\n", nlines);
}