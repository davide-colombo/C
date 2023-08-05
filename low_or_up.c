
#include <stdio.h>
#include <stdlib.h>

static char *stripat(const char *src, size_t pos);
static char *struniq(const char *src, char c);
static char *stripch(const char *src, char c);
static size_t strpos(const char *src, char c);
static size_t lenof(const char *src);

static int isalpha(int c);
static int islower(int c);
static int isupper(int c);

static size_t countupper(const char *src);
static size_t countlower(const char *src);

// ============================================================================
// global variables
static char *valid_low[] = {"l", "low", "lower"};
static char *valid_up[] = {"u", "up", "upper"};

// ============================================================================
// main
int main(int argc, char **argv){

    char *s;

    // remove '.'
    s = stripat(argv[0], 0);
    if(s == NULL){
        perror("low_or_up.c: remove '.' failed");
        exit(EXIT_FAILURE);
    }

    // remove '/'
    s = stripat(s, 0);
    if(s == NULL){
        perror("low_or_up.c; remove '/' failed");
        exit(EXIT_FAILURE);
    }

    printf("isalpha(argv[0][4]) = %d\n", isalpha(argv[0][4]));
    printf("islower(argv[0][4]) = %d\n", islower(argv[0][4]));
    printf("isupper(argv[0][4]) = %d\n", isupper(argv[0][4]));

    printf("countupper(\"HELLo\") = %zu\n", countupper("HELLo"));
    printf("countlower(\"HELLo\") = %zu\n", countlower("HELLo"));

    // free memory
    if(s != NULL) free((void *)s);

    /* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
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

    char *s2;
    s2 = struniq(argv[0], 'o');
    if(s2 != NULL){
        puts(s2);
        printf("lenof(s2) = %zu\n", lenof(s2));
    }

    if(s != NULL)
        free((void *)s);
    
    if(s1 != NULL)
        free((void *)s1);

    if(s2 != NULL)
        free((void *)s2);
    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */

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

// struniq
static char *struniq(const char *src, char c){
    size_t srclen = lenof(src);
    char *dst = malloc(srclen+1);
    if(dst == NULL){
        fprintf(stderr, "struniq(): malloc failed\n");
        return NULL;
        // string too large to handle
        // try to scompose the string into substring
        // perhaps recursive
    }

    char *tmp = src;
    char *dtmp = dst;
    int currch, nextch;
    do{
        currch = *tmp;
        if(currch == c){
            char *tnext = tmp+1;
            nextch = *tnext;
            while((currch - nextch) == 0){
                ++tmp, ++tnext;
                currch = *tmp;
                nextch = *tnext;
            }
        }

        *dtmp = *tmp;
        if(currch == '\0') break;
        ++dtmp, ++tmp;
    }while(1);

    size_t dstlen = lenof(dst);
    if(dstlen < srclen){
        char *tmp = realloc(dst, dstlen);
        if(tmp == NULL){
            fprintf(stderr, "struniq: realloc failed\n");
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

// ============================================================================
// isalpha
static int isalpha(int c){
    int ll = c - 65;
    int lu = c - 90;
    int ul = c - 97;
    int uu = c - 122;

    int llmask = ll >= 0;
    int lumask = lu <= 0;
    int ulmask = ul >= 0;
    int uumask = uu <= 0;
    
    return (llmask && lumask) || (ulmask && uumask);
}

// ============================================================================
// islower
static int islower(int c){
    int ul = c - 97;
    int uu = c - 122;

    int ulmask = ul >= 0;
    int uumask = uu <= 0;
    
    return (ulmask && uumask);
}


// ============================================================================
// isupper
static int isupper(int c){
    int ll = c - 65;
    int lu = c - 90;

    int llmask = ll >= 0;
    int lumask = lu <= 0;

    return (llmask && lumask);
}

// ============================================================================
// countupper
static size_t countupper(const char *src){
    size_t n = 0;
    char *tmp = src;
    int ch = *src;
    while(ch != '\0'){
        if(isupper(ch)) ++n;
        ++tmp;
        ch = *tmp;
    }
    return n;
}

// ============================================================================
// countlower
static size_t countlower(const char *src){
    size_t n = 0;
    char *tmp = src;
    int ch = *src;
    while(ch != '\0'){
        if(islower(ch)) ++n;
        ++tmp;
        ch = *tmp;
    }
    return n;
}
