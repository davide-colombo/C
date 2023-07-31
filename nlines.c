
#include <stdio.h>

#define NEWLINE 10

int main(){

    int c;
    int nlines = 0;
    
    /////////////////////////////////////////////////////////////////////
    // nlines.s
    // using O3 optimization

    /*
    ;; setup block
        ...
        ...
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

   // C code
    /*while((c = getchar()) != EOF)
        if(c == NEWLINE)
            ++nlines;*/

    
    /////////////////////////////////////////////////////////////////////
    // Using do-while
    // nlines.s
    // using O2 optimization

    /*
    ;; setup block
        ...
        ...
    DO:
        branch and link -> getchar
        compare char to target
        compare increment if equal (cinc)
        compare negative
        branch not equal to DO

    ;; cleanup block here after
        ...
        ...
    */

    // C code
    do{
        c = getchar();
        if(c == NEWLINE) nlines = nlines + 1;
    }while(c != EOF);

    // Commented just for looking at the assembly generated
    // printf("nlines = %d\n", nlines);
    return nlines;
}
