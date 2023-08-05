// Davide Colombo
// Saturday, 5 August 2023

// ============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// ============================================================================
#define MAX_LINE_LIM_STRCOPY    1000
#define BUFFER_SIZE_STRCOPY     100
#define BUFFER_INITIAL_STRCOPY  10

// ============================================================================
// function prototype, internal linkage
static size_t mystrlen(const char *src);
static size_t mygetline(char **linedst, size_t lim);
static char *mystrcp(const char *src, size_t srclen);
static char *mystrch(char *src, size_t choff, size_t srclen);

// ============================================================================
// main
int main(int argc, char **argv){

    char *linebuf;
    char *linebuf1;
    char *linebuf2;

    char *cpbuffer;
    size_t linesize;
    while( (linesize = mygetline(&linebuf, MAX_LINE_LIM_STRCOPY)) > 0){
        puts(linebuf);
        printf("linesize = %zu\n", linesize);
        printf("mystrlen(linebuf) = %zu\n", mystrlen(linebuf));

        if(linebuf != NULL){
            linebuf1 = mystrch(linebuf, 4, linesize);
            linebuf2 = mystrch(linebuf, 7, linesize);

            cpbuffer = mystrcp(linebuf, linesize);
            if(cpbuffer != NULL){
                puts(cpbuffer);
                printf("mystrlen(buffer) = %zu\n", mystrlen(cpbuffer));
            }

            if(linebuf1 != NULL){
                puts(linebuf1);
                printf("mystrlen(linebuf+4) = %zu\n", mystrlen(linebuf1));
            }
            
            if(linebuf2 != NULL){
                puts(linebuf2);
                printf("mystrlen(linebuf+7) = %zu\n", mystrlen(linebuf2));
            }
        }
    }

    if(linebuf != NULL)
        free((void *)linebuf);

    if(cpbuffer != NULL)
        free((void *)cpbuffer);

    return EXIT_SUCCESS;
}

// ============================================================================
// mystrcp
static char *mystrcp(const char *src, size_t srclen){
    size_t dstbytes = srclen + 1;
    char *dst = malloc(dstbytes);
    if(dst == NULL){
        perror("strcopy.c: mystrcp(), dst allocation");
        exit(EXIT_FAILURE);
    }

    for(size_t i = 0; (dst[i] = src[i]) != '\0'; ++i)
        ;
    return dst;
}

// ============================================================================
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

// ============================================================================
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

    // this is a must
    // arguments to a function are passed 'by value'
    // pointers are copied
    // the memory location pointed to 'linebuf' from the main() points to garbage
    // the same value is passed to the mygetline() function
    // how? it is copied onto the stack
    // NOTE: it is copied!
    // We need to store the address of the block of memory allocated with malloc() at the
    //  memory address of the 'linebuf' pointer of main(), not that of mygetline().
    *linedst = linebuf;

    if(c == EOF) return 0;
    return bufindx;
}

// ============================================================================
// mystrch
// take a string and return a pointer to the character past choff bytes
// it is implemented in this way because if we want to apply the same
// function to the same string many times and we have a check for null
// then a call to mystrlen(), we end up wasting precious cycles.
static char *mystrch(char *src, size_t choff, size_t srclen){
    if(choff >= srclen) return NULL;
    return src+choff;
}