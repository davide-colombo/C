
#include <stdio.h>
#include <stdlib.h>

#define ASCII_LB_UPPERALPHA 65
#define ASCII_UB_UPPERALPHA 90
#define ASCII_LB_LOWERALPHA 97
#define ASCII_UB_LOWERALPHA 122

static char *stripat(const char *src, size_t pos, size_t srclen);
static char *struniq(const char *src, char c, size_t srclen);
static char *stripch(const char *src, char c, size_t srclen);
static size_t strmatch(const char *src, const char *dst);
static size_t strpos(const char *src, char c);
static size_t strsum(const char *src);
static size_t lenof(const char *src);

static int isalpha(int c);
static int islower(int c);
static int isupper(int c);

static size_t countupper(const char *src);
static size_t countlower(const char *src);
static size_t countch_range(const char *src, int lb, int ub);

static int charmin(const char *src);
static int charmax(const char *src);
static float charmean(const char *src, size_t ssum, size_t slen);

// ============================================================================
// global variables
static char *valid_low[] = {"l", "low", "lower"};
static char *valid_up[] = {"u", "up", "upper"};

// ============================================================================
// main
int main(int argc, char **argv){

    char *s;
    size_t slen = lenof(s);

    // remove '.'
    s = stripat(argv[0], 0, slen);
    if(s == NULL){
        perror("low_or_up.c: remove '.' failed");
        exit(EXIT_FAILURE);
    }

    // remove '/'
    s = stripat(s, 0, slen);
    if(s == NULL){
        perror("low_or_up.c; remove '/' failed");
        exit(EXIT_FAILURE);
    }

    size_t m = strmatch(s, argv[0]);
    printf("\"%s\" == \"%s\" ? %zu\n", s, argv[0], m);

    slen = lenof(s);
    char *cmp = struniq(s, 'o', slen);

    m = strmatch(s, cmp);
    printf("\"%s\" == \"%s\" ? %zu\n", s, cmp, m);
    printf("lenof(s) = %zu\n", slen);

    size_t ssum = strsum(s);
    printf("strsum(s) = %zu\n", ssum);

    ssum = strsum(argv[0]);
    printf("strsum(argv[0]) = %zu\n", ssum);

    // CHARMIN
    int cmin;
    cmin = charmin(s);
    printf("charmin(s) = '%c' (%d)\n", cmin, cmin);

    // CHARMAX
    int cmax;
    cmax = charmax(s);
    printf("charmax(s) = '%c' (%d)\n", cmax, cmax);

    // CHARMEAN
    float cmean;
    cmean = charmean(s, 0, 0);
    int avgchar = (int) cmean;
    printf("charmean(s) = %3.2f ('%c', %d)\n", cmean, avgchar, avgchar);

    /* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    printf("isalpha(argv[0][4]) = %d\n", isalpha(argv[0][4]));
    printf("islower(argv[0][4]) = %d\n", islower(argv[0][4]));
    printf("isupper(argv[0][4]) = %d\n", isupper(argv[0][4]));

    printf("countupper(\"HELLo\") = %zu\n", countupper("HELLo"));
    printf("countlower(\"HELLo\") = %zu\n", countlower("HELLo"));
    printf("countch_range(text, 65, 90) = %zu\n", countch_range(argv[0], ASCII_LB_UPPERALPHA, ASCII_UB_UPPERALPHA));
    printf("countch_range(text, 97, 122) = %zu\n", countch_range(argv[0], ASCII_LB_LOWERALPHA, ASCII_UB_LOWERALPHA));
    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */

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
// strmatch
// return index of the first mismatch
// return 0 if one of the two strings is empty
// return 0 if one string is shorter
// if exact match the value returned is exactly equal to the value returned to by 'lenof()'
static size_t strmatch(const char *src, const char *cmp){
    size_t i = 0;
    register int sch = *src;
    register int cch = *cmp;
    do{
        if(sch != cch) break;
        if(sch == '\0') return i;       // sch == cch implicit because no break
        ++src, ++cmp;
        sch = *src;
        cch = *cmp;
        ++i;
    }while(1);

    return i;
}

// ============================================================================
// strsum
static size_t strsum(const char *src){
    size_t sum = 0;
    register int c = *src;
    do{
        sum += c;
        ++src;
        c = *src;
    }while(c != '\0');

    return sum;
}

// ============================================================================
// charmin
// get the minimum ASCII code of the characters in the string
// do not include '\0' (i.e., zero)
// return 0 if empty string
static int charmin(const char *src){
    register int c = *src;
    register int cmin = *src;
    do{
        if(c == '\0') break;
        if(c < cmin)
            cmin = c;
        ++src;
        c = *src;
    }while(1);

    return cmin;
}


// ============================================================================
// charmax
// get the maximum char from the
static int charmax(const char *src){
    register int c = *src;
    register int cmax = *src;
    do{
        if(c == '\0') break;
        if(c > cmax)
            cmax = c;
        ++src;
        c = *src;
    }while(1);

    return cmax;
}

// ============================================================================
// charmean
static float charmean(const char *src, size_t ssum, size_t slen){
    if(ssum == 0) ssum = strsum(src);
    if(slen == 0) slen = lenof(src);

    float num = (float) ssum;
    float den = (float) slen;
    return (num / den);
}

// ============================================================================
//stripat
static char *stripat(const char *src, size_t pos, size_t srclen){

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
    register size_t pos;
    register char *tmp;
    register int ch;
    pos = 0;
    tmp = src;
    ch = *src;
    do{
        if(ch == '\0' || ch == c) break;
        ++pos, ++tmp;
        ch = *tmp;
    }while(1);
    return pos;
}

// ============================================================================
// stripch
static char *stripch(const char *src, char c, size_t srclen){
    // malloc
    char *dst = malloc(srclen+1);
    if(dst == NULL){
        fprintf(stderr, "stripch(): malloc failed\n");
        return NULL;
    }
    
    // hint to the processor
    register char *tmp = src;
    register char *dtmp = dst;
    register int src_ch;

    // counter for number of stripped char
    // helps to avoid the function call to 'lenof()'
    int nchstripped = 0;
    do{
        src_ch = *tmp;
        while(src_ch == c){
            ++nchstripped, ++tmp;
            src_ch = *tmp;
        }
        
        // copy onto destination
        *dtmp = src_ch;
        if(src_ch == '\0') break;
        ++dtmp, ++tmp;
    }while(1);

    // realloc
    // do not call a function from here inside
    // this is much better, reduce the bubbles in the code
    // avoid branches
    if(nchstripped){
        size_t dstlen = srclen - nchstripped + 1;
        tmp = realloc(dst, dstlen);
        if(tmp == NULL){
            fprintf(stderr, "stripch(): realloc failed\n");
            return NULL;
        }
        dst = tmp;
    }

    return dst;
}

// ============================================================================
// struniq
static char *struniq(const char *src, char c, size_t srclen){
    // malloc
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
    register int currch, nextch;
    int nchstripped = 0;
    do{
        currch = *tmp;
        if(currch == c){
            char *tnext = tmp+1;
            nextch = *tnext;
            int chdiff = currch - nextch;
            while(chdiff == 0){
                ++nchstripped;++tmp, ++tnext;
                currch = *tmp;
                nextch = *tnext;
                chdiff = currch - nextch;
            }
        }

        *dtmp = *tmp;
        if(currch == '\0') break;
        ++dtmp, ++tmp;
    }while(1);

    // avoid branch to 'lenof()'
    if(nchstripped){
        size_t dstlen = srclen - nchstripped + 1;
        tmp = realloc(dst, dstlen);
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
    size_t index = 0;
    char *tmp = src;
    register int ch = *src;
    do{
        if(ch == '\0') break;
        ++index, ++tmp;
        ch = *tmp;
    }while(1);
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
        // rethinking about the cost of calling the function may be worth
        // depending on the context

        // testing may be highly unpredicatable, therefore the Branch Prediction Unit may cause stalls
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

// ============================================================================
// count char in range
// lb: lower bound (included)
// up: upper bound (included)
static size_t countch_range(const char *src, int lb, int ub){
    size_t n = 0;
    register int ch = *src;
    while(ch != '\0'){
        uint32_t chsublb = (uint32_t) ((int32_t)(ch - lb) >> 31);
        uint32_t chsubub = (uint32_t) ((int32_t)(ch - ub) >> 31);

        uint32_t res1 = (chsublb & 0) | (~chsublb & 1);                             // ch >= lb ? 1 : 0
        uint32_t res2 = (chsubub & res1) | (~chsubub & 0);                          // ch <= ub ? 1 : 0

        n += res2;

        ++src;
        ch = *src;
    }
    return n;
}