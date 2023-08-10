
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S_GET_LINE_BUFSIZE 64

typedef enum {
    S_GET_LINE_UNSET = -2,
    S_GET_LINE_EOF = -1,
    S_GET_LINE_SUCCESS = 0,
    S_GET_LINE_NULL_BUFFER,
    S_GET_LINE_ZERO_BUFSIZE,
    S_GET_LINE_INVALID_BUFIDX
} err_t;

char *error_msg[] = {
    "success",
    "invalid 'buffer': NULL",
    "invalid 'bufsize': 0",
    "invalid 'bufidx': >= 'bufsize'"
};

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

static err_t s_get_line_write(char *buffer, size_t bufsize);
static err_t s_get_line_append(char *buffer, size_t bufsize, size_t bufidx);
static err_t __s_get_line_core(char *buffer, size_t bufsize, size_t bufidx);

// Statically allocated arrays MUST NOT be declared as LOCAL VARIABLES.
char buffer[S_GET_LINE_BUFSIZE];
char initialized_buffer[] = "Hello, this is a very happy day!";

// ============================================================================
int main(int argc, char **argv){
    
    fprintf(stdout, "\n<TEST WRITE>\n");

    // char *buffer;       /* DANGEROUS */
    err_t status;

    // Test 1
    if( (status = s_get_line_write(buffer, S_GET_LINE_BUFSIZE)) != S_GET_LINE_SUCCESS )
        fprintf(stderr, "%s\n", error_msg[status]);
    puts(buffer);

    if( (status = s_get_line_write(buffer, S_GET_LINE_BUFSIZE)) != S_GET_LINE_SUCCESS )
        fprintf(stderr, "%s\n", error_msg[status]);
    puts(buffer);

    // Test NULL
    if( (status = s_get_line_write(NULL, 10)) != S_GET_LINE_SUCCESS )
        fprintf(stderr, "%s\n", error_msg[status]);

    // Test 'bufsize' 0
    if( (status = s_get_line_write(buffer, 0)) != S_GET_LINE_SUCCESS)
        fprintf(stderr, "%s\n", error_msg[status]);

    // Test bufsize much larger than actual 'buffer' size
    // this is UNDEFINED and DANGEROUS
    //if( s_get_line_write(buffer, 128) == NULL )
    //    fprintf(stderr, "failed\n");

    fprintf(stdout, "\n<TEST APPEND>\n");
    size_t init_buf_size = sizeof initialized_buffer;

    if( (status = s_get_line_append(initialized_buffer, init_buf_size, 16)) != S_GET_LINE_SUCCESS )
        fprintf(stderr, "%s\n", error_msg[status]);
    puts(initialized_buffer);

    if( (status = s_get_line_append(initialized_buffer, init_buf_size, 0)) != S_GET_LINE_SUCCESS )
        fprintf(stderr, "%s\n", error_msg[status]);
    puts(initialized_buffer);

    // Consume all remaining lines
    while( (status = s_get_line_write(buffer, S_GET_LINE_BUFSIZE)) != S_GET_LINE_EOF ){
        if(status != S_GET_LINE_SUCCESS){
            fprintf(stderr, "%s\n", error_msg[status]);
            exit(EXIT_FAILURE);
        }
        puts(buffer);
    }

    return 0;
}

// ============================================================================
/* Read at most 'bufsize - 1' bytes, overwrite the content of 'buffer', 
 * do not reallocate.
 */
static err_t s_get_line_write(char *buffer, size_t bufsize){
    if(buffer == NULL) return S_GET_LINE_NULL_BUFFER;
    if(bufsize == 0) return S_GET_LINE_ZERO_BUFSIZE;
    return __s_get_line_core(buffer, bufsize, 0);
}

// ============================================================================
/* Read at most 'bufsize - bufidx - 1' bytes, append the content starting at 
 * 'bufidx', do not reallocate 
 */
static err_t s_get_line_append(char *buffer, size_t bufsize, size_t bufidx){
    if(buffer == NULL) return S_GET_LINE_NULL_BUFFER;
    if(bufsize == 0) return S_GET_LINE_ZERO_BUFSIZE;
    if(bufidx >= bufsize) return S_GET_LINE_INVALID_BUFIDX;
    return __s_get_line_core(buffer - bufidx, bufsize + bufidx, bufidx);
}

// ============================================================================
static err_t __s_get_line_core(char *buffer, size_t bufsize, size_t bufidx){
    err_t status = S_GET_LINE_UNSET;
    do{
        int tmpc = getchar();

        // masks
        uint32_t eof_mask = (uint32_t) (((int32_t)(tmpc == EOF) << 31) >> 31);
        uint32_t eol_mask = (uint32_t) (((int32_t)(tmpc == '\n') << 31) >> 31);
        uint32_t eob_mask = (uint32_t) (((int32_t)(bufsize <= 2) << 31) >> 31);

        // values
        int tmpchar1 = (eof_mask & '\0') | (~eof_mask & tmpc);
        int tmpchar2 = (eol_mask & '\0') | (~eol_mask & tmpchar1);

        int tmpstatus1 = (eof_mask & S_GET_LINE_EOF) | (~eof_mask & status);
        int tmpstatus2 = (eol_mask & S_GET_LINE_SUCCESS) | (~eol_mask & tmpstatus1);
        int tmpstatus3 = (eob_mask & S_GET_LINE_SUCCESS) | (~eob_mask & tmpstatus2);
        
        int tmpmove1 = (eof_mask & 0) | (~eof_mask & 1);
        int tmpmove2 = (eol_mask & 0) | (~eol_mask & tmpmove1);
        int tmpmove3 = (eob_mask & 1) | (~eob_mask & tmpmove2);

        // stores
        status      = tmpstatus3;
        *buffer     = tmpchar2;
        buffer      += tmpmove3;
        bufsize     -= tmpmove3;

        // extra increment to to add '\0' in case of END-OF-BUFFER
        int tmpchar3 = (eob_mask & '\0') | (~eob_mask & tmpchar2);
        *buffer = tmpchar3;
    }while(status == S_GET_LINE_UNSET);

    return status;
}
