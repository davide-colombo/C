
#include <stdio.h>

#define NEWLINE 10

int main(){

    int c;
    int nlines = 0;

    // nlines.s
    // using O3 optimization
    
    /*
    WHILE:
        branch and link -> getchar
        compare with EOF
        branch equal to CLEANUP

     ;; second block (enters the while loop)
        compare character with target
        branch not equal to WHILE

    ;; third block (enters the if)
        increment counter
        jump to WHILE

    CLEANUP:
        move result into x0
        restore the stack
        return 
    */

    while((c = getchar()) != EOF)
        if(c == NEWLINE)
            ++nlines;
    
    // Commented just for looking at the assembly generated
    // printf("nlines = %d\n", nlines);
    return nlines;
}