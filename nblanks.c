
#include <stdio.h>
#include <stdint.h>

#define HTAB 0x0009     // 0000 1001
#define NEWL 0x000A     // 0000 1010
#define SPCE 0x0020      // 0010 0000

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
    uint64_t nchars;
    nchars = 0;

    do{
        c = getchar();
        //nl += !((c ^ NEWL) | (c & ~NEWL));      // same as (c == NEWL)
        //ns += !((c ^ SPCE) | (c & ~SPCE));      // same as (c == SPCE)
        //nt += !((c ^ HTAB) | (c & ~HTAB));      // same as (c == HTAB)
        uint32_t nwl_eq = (c == NEWL);
        uint32_t spc_eq = (c == SPCE);
        uint32_t tab_eq = (c == HTAB);

        nchars += nwl_eq + spc_eq + tab_eq;

        /*nl += (c == NEWL);
        ns += (c == SPCE);
        nt += (c == HTAB);*/
    } while(c != EOF);
    
    // Make the two ADD instructions independent
    //uint64_t nchars_1 = nl + ns;
    //uint64_t nchars_2 = nt + 0;
    //uint64_t nchars = nchars_1 + nchars_2;

    printf("nchars = %llu\n", nchars);
    return 0;
}
