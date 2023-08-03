
#include <stdio.h>
#include <stdint.h>

#define HTAB 9
#define NEWL 10
#define SPC 32

int main(){

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

    int32_t c;
    uint32_t nl, ns, nt;            // newline, space, tab counter
    nl = ns = nt = 0;               // initialize counters
    do{
        c = getchar();
        nl += (c == NEWL);
        ns += (c == SPC);
        nt += (c == HTAB);
    } while(c != EOF);
    
    uint64_t nchars_1 = nl + ns;
    uint64_t nchars = nchars_1 + nt;

    printf("nchars = %llu\n", nchars);
    return 0;
}
