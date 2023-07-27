
#include <stdio.h>

main(){

    double nchars;

    for(nchars = 0; getchar() != EOF; ++nchars)
        ;
    printf("The total number of characters is %.0lf\n", nchars);
}