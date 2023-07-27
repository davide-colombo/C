
#include <stdio.h>

main(){

    long nchars;

    nchars = 0;
    while(getchar() != EOF)
        ++nchars;
    printf("The total number of characters is %ld\n", nchars);
}