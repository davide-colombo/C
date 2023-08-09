
#include <stdio.h>
#include <stdlib.h>

#define S_GET_LINE_BUFSIZE 64

/* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 * 'buffer' should point to a writable memory location;
 * 
 * returns NULL if 'buffer' is NULL;
 * 
 * returns the memory address stored in 'buffer' if lines are successfully read;
 * 
 * Read at most 'bufsize - 1' bytes;
 * Stop when the first '\n' character is read;
 * Stop when EOF is read;
 * 
 * 'buffer' is safely ended with '\0' to conform to the C standard format
 *      of strings;
 * 
 * Do not reallocate memory;
 * 
 * These functions makes no assumption about origin of memory type of 
 *      'buffer', whether it is statically or dynamically allocated;
 * 
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */

static char *s_get_line_write(char *buffer, size_t bufsize);
static char *s_get_line_append(char *buffer, size_t bufsize, size_t bufidx);

// Statically allocated arrays MUST NOT be declared as LOCAL VARIABLES.
char buffer[S_GET_LINE_BUFSIZE];

// ============================================================================
int main(int argc, char **argv){
    
    // char *buffer;       /* DANGEROUS */

    if( s_get_line_write(buffer, S_GET_LINE_BUFSIZE) == NULL){
        fprintf(stderr, "failed\n");
        exit(EXIT_FAILURE);
    }

    puts(buffer);

    return 0;
}

// ============================================================================
/* Read at most 'bufsize - 1' bytes, overwrite the content of 'buffer', 
 * do not reallocate.
 */
static char *s_get_line_write(char *buffer, size_t bufsize){
    if(buffer == NULL) return NULL;
    if(bufsize == 0) return NULL;

    do{
        int tmpc = getchar();

        uint32_t eof_mask = (uint32_t) (((int32_t)(tmpc == EOF) << 31) >> 31);
        uint32_t eol_mask = (uint32_t) (((int32_t)(tmpc == '\n') << 31) >> 31);
        uint32_t eob_mask = (uint32_t) (((int32_t)(bufsize <= 1) << 31) >> 31);

        int tmpchar1 = (eof_mask & '\0') | (~eof_mask & tmpc);
        int tmpchar2 = (eol_mask & '\0') | (~eol_mask & tmpchar1);
        int tmpchar3 = (eob_mask & '\0') | (~eob_mask & tmpchar2);

        *buffer = tmpchar3;
        if(!tmpchar3) break;    // first store, then break
        buffer += 1;
        bufsize -= 1;
    }while(1);

    return buffer;
}

// ============================================================================
/* Read at most 'bufsize - bufidx - 1' bytes, append the content starting at 
 * 'bufidx', do not reallocate 
 */
static char *s_get_line_append(char *buffer, size_t bufsize, size_t bufidx){
    if(buffer == NULL) return NULL;

    return buffer;
}
