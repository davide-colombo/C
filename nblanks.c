
#include <stdio.h>

int main(){

    int c;
    long nchars;

    /////////////////////////////////////////////////////////////////
    // nblanks.s
    // compiled with O2 level

    /*
    ;; setup block
        ...
    
    INC:
        increment
    
    GETCHAR:
        branch and link -> getchar()
        substract #9 to the character
        compare the result of subtraction with #2 (unsigned 32-bit comparison)
        branch if lower (b.lo) to INC
    
    ;; block 3
        compare char to -1 (EOF)
        branch equal to PRINTF

    ;; block 4
        unsigned 32-bit comparison of character with #32 (space in ASCII)
        branch not equal to GETCHAR
        jump to INC

    ;; cleanup block
        ...
    */

   // C code
    /*nchars = 0;
    while((c = getchar()) != EOF)
        if(c == '\t' || c == ' ' || c == '\n')
            ++nchars;*/

    // Commented out for inspecting assembly file
    //printf("Total blanks, tabs, lines is %ld\n", nchars);

    /////////////////////////////////////////////////////////////////
    // nblanks.s, do-while version
    // compiled with O2 level

    // The generated instructions are much better, without bubbles due to branches.

    // C code
    do{
        c = getchar();
        if(c == '\t' || c == '\n' || c == ' ') nchars = nchars + 1;
    } while(c != EOF);

    return nchars;
}
