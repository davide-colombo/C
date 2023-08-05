
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_LINE_LIM_STRCOPY    1000
#define BUFFER_SIZE_STRCOPY     100
#define BUFFER_INITIAL_STRCOPY  10

// function prototype, internal linkage
static char *mystrcp(const char *src, char *dst);
static size_t mystrlen(const char *src);
static size_t mygetline(char **linedst, size_t lim);

int main(int argc, char **argv){

    // LEN automatically cast to 'size_t'
    // returned type automatically cast to 'char *'
    // sizeof char always equal to 1 byte, no need to multiply
    char *buffer = malloc(BUFFER_SIZE_STRCOPY);
    if(buffer == NULL){
        perror("main(), line 17: failed to allocate memory for 'buffer'");
        exit(EXIT_FAILURE);
    }

    char *linebuf;
    size_t linesize;
    while( (linesize = mygetline(&linebuf, MAX_LINE_LIM_STRCOPY)) > 0){
        puts(linebuf);
        printf("linesize = %zu\n", linesize);
    }

    if(linebuf == NULL){
        errno = 1;
    }

    if(buffer != NULL)
        free((void *)buffer);

    if(errno) exit(EXIT_FAILURE);
    return EXIT_SUCCESS;
}

// mystrcp
// take the string pointed to by src and copy it in dst
static char *mystrcp(const char *src, char *dst){
    if(src == NULL || dst == NULL) return NULL;
    if((mystrlen(dst) - mystrlen(src)) >= 0)
        for(size_t i = 0; (dst[i] = src[i]) != '\0'; ++i)
            ;
    return dst;
}

// mystrlen
// take a string and return it's length without '\0'
static size_t mystrlen(const char *src){
    if(src == NULL)
        return 0;
    size_t i;
    for(i = 0; src[i] != '\0'; ++i)
        ;
    return i;
}

// mygetline
static size_t mygetline(char **linedst, size_t lim){

    // underflow
    if((lim - 1) > lim){
        fprintf(stderr, "strcopy.c: mygetline(), invalid value %zu for argument 'lim'\n", lim);
        *linedst = NULL;
        return 0;
    }

    // initial buffer
    char *linebuf = malloc(BUFFER_INITIAL_STRCOPY);
    if(linebuf == NULL){
        fprintf(stderr, "strcopy.c: mygetline(), initial call to malloc, linebuf is NULL\n");
        return 0;
    }

    size_t bufsize = BUFFER_INITIAL_STRCOPY;
    size_t bufindx = 0;
    char *tmpbuf;
    lim -= 1;

    register int32_t c;
    do{
        // realloc
        if(bufindx >= bufsize){
            bufsize *= 2;
            if(bufsize >= lim)
                bufsize = lim + 1;      // +1 because decremented before

            /* =========================================================
            // bufsize overflow
            // we can comment this out because of 'lim'
            // even if lim == UINT64_MAX, we are adding 1 to 'lim-1'

            if(bufindx >= bufsize){
                fprintf(stderr, "mygetline(): nchmax overflow\n");
                free((void *)linebuf);
                return NULL;
            }

            ========================================================= */

            // temporary buffer
            tmpbuf = realloc(linebuf, bufsize);
            if(tmpbuf == NULL){
                free((void *)linebuf);
                linebuf = NULL;
                return 0;
            }

            // new memory
            linebuf = tmpbuf;
        }

        // read
        if( (c = getchar()) == EOF ) break;
        
        // store
        linebuf[bufindx++] = c;

    }while(bufindx < lim && c != '\n');
    
    // end character buffer
    linebuf[bufindx] = '\0';

    // rescale to precise size if there is extra space
    // NOTE: lim is equal to lim-1 because indices goes from 0 to lim-1
    if(bufindx < lim){
        tmpbuf = realloc(linebuf, bufindx+1);
        if(tmpbuf == NULL){
            fprintf(stderr, "strcopy.c: mygeline(), failed to resize linebuf to %zu bytes\n", (bufindx+1));
            free((void *)linebuf);
            linebuf = NULL;
            return 0;
        }
        linebuf = tmpbuf;
    }

    *linedst = linebuf;
    if(c == EOF) return 0;
    return bufindx;
}