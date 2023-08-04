
#include <stdio.h>
#include <stdint.h>

#define MAXLINE     1000

static int mygetline(char line[], int32_t lim);

int main(int argc, char *argv[]){

    int32_t len;
    char line[MAXLINE];
    while((len = mygetline(line, MAXLINE)) > 0){
        printf("%s\n", line);
        printf("len = %d\n", len);
    }

    return 0;
}

// internal linkage
static int mygetline(char s[], int32_t lim){

    int32_t c, i;

    i = 0;
    lim -= 2;
    do{
        c = getchar();
        if(c == EOF){
            break;
        }else{
            s[i] = c;
            i++;
        }

        if(i >= lim || c == '\n') break;

    }while(1);

    s[i] = '\0';
    return i;
}
