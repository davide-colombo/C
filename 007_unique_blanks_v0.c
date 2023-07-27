
#include <stdio.h>

#define MATCH ' '

main(){

    int c;          // current char
    int lc;         // last char

    lc = 0;
    while((c = getchar()) != EOF){
        int lmatch = (lc == MATCH);
        int cmatch = (c == MATCH);

        if(lmatch && cmatch)
            continue;
        putchar(c);
        lc = c;
    }
}
