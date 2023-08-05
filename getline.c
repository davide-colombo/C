
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAXL    (uint32_t) 100
#define EOL     (uint32_t) 0x0000000A
#define NUL     (uint32_t) 0x00000000

static uint32_t mygetline(char *s, uint32_t lim);

int main(int argc, char *argv[]){

    char *lp;
    lp = malloc(sizeof(char) * MAXL);
    if(lp == NULL){
        printf("error\n");
        return 1;
    }

    size_t len;
    while((len = mygetline(lp, MAXL)) > 0){
        puts(lp);
        printf("len = %zu\n", len);
    }

    if(lp != NULL)
        free((void *)lp);

    return 0;
}

// internal linkage
static uint32_t mygetline(char *s, uint32_t lim){

    register int32_t c;
    char *tmp = s;
    do{
        c = getchar();

        uint32_t eof_mask = (uint32_t) (((int32_t) (c == EOF) << 31) >> 31);
        uint32_t eol_mask = (uint32_t) (((int32_t) (c == EOL) << 31) >> 31);
        uint32_t lim_mask = (uint32_t) (((int32_t) (lim > 1) << 31) >> 31);

        // next possible limit
        uint32_t ldec = lim - 1;                                                        // if lim == 0, then lim1 = UINT32_MAX

        // update lim
        uint32_t lim1 = (lim_mask & ldec) | (~lim_mask & 0);
        uint32_t lim2 = (eof_mask & 0) | (~eof_mask & lim1);                            // set to 0 if EOF
        uint32_t lim3 = (eol_mask & 0) | (~eol_mask & lim2);                            // set to 0 if EOL
        lim = lim3;

        // update *tmp
        uint32_t tmp1 = (~eof_mask & c) | (eof_mask & NUL);
        uint32_t tmp2 = (lim_mask & tmp1) | (~lim_mask & NUL);
        *tmp = tmp2;

        // update tmp
        uint32_t tinc1 = (~eof_mask & 1) | (eof_mask & 0);
        uint32_t tinc2 = (lim_mask & tinc1) | (~lim_mask & 0);
        tmp += tinc2;

        // extra update tmp if EOL
        uint32_t tince1 = (eol_mask & 0) | (~eol_mask & 1);
        uint32_t tince2 = (eof_mask & 0) | (~eof_mask & tince1);
        tmp -= tince2;

        // extra update *tmp if EOL
        uint32_t tmpe = (eol_mask & NUL) | (~eol_mask & tmp2);
        *tmp = tmpe;

        // re-apply the increment in case c != EOL
        uint32_t tincr = (eol_mask & 0) | (~eol_mask & tinc2);
        tmp += tincr;

    }while(lim > 0);
    return (uint32_t)((tmp - s) / sizeof(char));
}
