
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_LINE_LIM_STRCOPY    1000
#define BUFFER_SIZE_STRCOPY     100

// function prototype, internal linkage
static char *mystrcp(const char *src, char *dst);
static size_t mystrlen(const char *src);
static char *mygetline(size_t lim);

int main(int argc, char **argv){

    // LEN automatically cast to 'size_t'
    // returned type automatically cast to 'char *'
    // sizeof char always equal to 1 byte, no need to multiply
    char *buffer = malloc(BUFFER_SIZE_STRCOPY);
    if(buffer == NULL){
        perror("main(), line 17: failed to allocate memory for 'buffer'");
        exit(EXIT_FAILURE);
    }

    if(buffer != NULL)
        free((void *)buffer);

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
static char *mygetline(size_t lim){

    char *linebuf = NULL;
    size_t nchmax = 0;
    size_t nchread = 0;
    char *tmpbuf;

    register int32_t c;
    while((c = getchar()) != EOF){
        if(nchread >= nchmax){
            nchmax += 20;
            if(nchread >= nchmax){
                fprintf(stderr, "mygetline(): nchmax overflow\n");
                free((void *)linebuf);
                return NULL;
            }

            // temporary buffer
            tmpbuf = realloc(linebuf, nchmax+1);
            if(tmpbuf == NULL){
                free((void *)linebuf);
                return NULL;
            }

            linebuf = tmpbuf;
        }

        if(c == '\n')
            break;
        
        linebuf[nchread++] = c;
    }
    if(linebuf != NULL)
        linebuf[nchread] = '\0';

}