
#include <stdio.h>
#include <stdlib.h>

static char *valid_low[] = {"l", "low", "lower"};
static char *valid_up[] = {"u", "up", "upper"};

static size_t strpos(const char *src, char c);
static char *stripch(const char *src, char c);
static char *stripat(const char *src, size_t pos);
static size_t lenof(const char *src);

// ============================================================================
// main
int main(int argc, char **argv){

    char *s;
    s = stripat(argv[0], 0);

    if(s != NULL){
        puts(s);
        printf("lenof(s) = %zu\n", lenof(s));
    }

    char *s1;
    s1 = stripch(argv[0], 'o');
    if(s1 != NULL){
        puts(s1);
        printf("lenof(s1) = %zu\n", lenof(s1));
    }

    if(s != NULL)
        free((void *)s);
    
    if(s1 != NULL)
        free((void *)s1);

    return 0;
}

// ============================================================================
//stripat
static char *stripat(const char *src, size_t pos){
    size_t srclen = lenof(src);

    // to avoid realloc later, allocate memory for 1 byte less!
    char *dst = malloc(srclen);
    if(dst == NULL){
        fprintf(stderr, "stripat(): malloc failed\n");
        return NULL;
    }

    char *tmp = src;
    char *dtmp = dst;
    char *trg = src+pos;
    int src_ch;
    do{
        src_ch = *tmp;
        if(tmp == trg){
            ++tmp;
            continue;
        }

        *dtmp = src_ch;
        if(src_ch == '\0') break;
        ++tmp, ++dtmp;
    }while(1);

    return dst;
}

// ============================================================================
// strpos
static size_t strpos(const char *src, char c){
    size_t pos;
    const char *tmp;
    for(pos = 0, tmp = src; *tmp != '\0' && *tmp != c; ++pos, ++tmp)
        ;
    return pos;
}

// ============================================================================
// stripch
static char *stripch(const char *src, char c){
    size_t srclen = lenof(src);
    char *dst = malloc(srclen+1);
    if(dst == NULL){
        fprintf(stderr, "stripch(): malloc failed\n");
        return NULL;
    }
    
    char *tmp = src;
    char *dtmp = dst;
    int src_ch;
    do{
        src_ch = *tmp;
        while(src_ch == c){
            ++tmp;
            src_ch = *tmp;
        }
        
        // copy onto destination
        *dtmp = src_ch;
        if(src_ch == '\0') break;
        ++dtmp, ++tmp;
    }while(1);

    // realloc
    size_t dstlen = lenof(dst);
    if(dstlen < srclen){
        char *tmp = realloc(dst, dstlen+1);
        if(tmp == NULL){
            fprintf(stderr, "stripch(): realloc failed\n");
            return NULL;
        }
        dst = tmp;
    }

    return dst;
}

// ============================================================================
static size_t lenof(const char *src){
    size_t index;
    // load address before the cycle
    char *tmp = src;
    for(index = 0; *tmp != '\0'; ++index, ++tmp)
        ;
    return index;
}
