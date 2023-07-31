
#include <stdio.h>

int main(){

    int c;
    long nchars;

    nchars = 0;
    while((c = getchar()) != EOF)
        if(c == '\t' || c == ' ' || c == '\n')
            ++nchars;
    printf("Total blanks, tabs, lines is %ld\n", nchars);
}