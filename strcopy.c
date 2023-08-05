
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define LEN 100

// function prototype, internal linkage
static char *mystrcp(const char *src, char *dst);
static size_t mystrlen(const char *s);

int main(int argc, char **argv){

    // LEN automatically cast to 'size_t'
    // returned type automatically cast to 'char *'
    // sizeof char always equal to 1 byte, no need to multiply
    char *s = malloc(LEN);
    if(s == NULL){
        perror("main(), line 17: failed to allocate memory for 's'");
        exit(EXIT_FAILURE);
    }

    mystrcp(s, NULL);                   // should return NULL
    mystrcp(NULL, NULL);                // should return NULL
    //mystrcp(s, d);                      // should return NULL if 'd' does not have enough space

    if(s != NULL)
        free((void *)s);

    return EXIT_SUCCESS;
}

// mystrcp
// take the string pointed to by src and copy it in dst
static char *mystrcp(const char *src, char *dst){
    if(src == NULL || dst == NULL) return NULL;
    if((mystrlen(dst) - mystrlen(src)) <= 0)
        for(size_t i = 0; (dst[i] = src[i]) != '\0'; ++i)
            ;
    return dst;
}

// mystrlen
// take a string and return it's length without '\0'
static size_t mystrlen(const char *s){
    if(s == NULL)
        return 0;
    size_t i;
    for(i = 0; s[i] != '\0'; ++i)
        ;
    return i;
}