
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAXLINE     (size_t) 1000

static size_t mygetline(char *s, size_t lim);

int main(int argc, char *argv[]){

    char *lp;
    lp = malloc(sizeof(char) * MAXLINE);
    if(lp == NULL){
        printf("error\n");
        return 1;
    }

    size_t len;
    while((len = mygetline(lp, MAXLINE)) > 0){
        puts(lp);
        printf("len = %zu\n", len);
    }

    if(lp != NULL)
        free((void *)lp);

    return 0;
}

// internal linkage
static size_t mygetline(char *s, size_t lim){

    int32_t c;
    size_t i;
    i = 0;
    lim -= 1;
    do{
        c = getchar();
        s[i] = c;
        i++;
    }while(c != '\n' && c != EOF && i < lim);
    
    if(c == EOF){
        i -= 1;
    }
    s[i] = '\0';
    return i;
}
