
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){

    /*
        This function takes a pointer and stores the output into the memory
        address pointed to by the pointer.

        However, the memory must be ALREADY pre-allocated!

        The function, does not handle allocation.

        A flow for this to work is:
        1 - alloc space
        2 - function call
        3 - check for error
    */

    char *dst = NULL;
    // strcat(dst, ", World!");
    // puts(dst);

    /*
        This proves the function handles the (eventual) re-allocation
        provided that it is necessary to concatenate the 'src' string. 
    */

    dst = malloc(2);
    if(dst == NULL){
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    strcat(dst, ", World!");
    puts(dst);
    free((void *)dst);

    return 0;
}