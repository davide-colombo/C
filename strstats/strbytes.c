
#include "strbytes.h"

// ============================================================================
// countbits
cntbit_t countbits(bytes_t nbytes){
    register cntbit_t c = 0;
    register bytes_t op1 = nbytes;
    register bytes_t op2 = nbytes - 1;
    do{
        bytes_t res = op1 & op2;
        nbytes = res;
        op1 = res;
        op2 = res - 1;
        ++c;
    }while(nbytes);
    return c;
}

// ============================================================================
// smallpow2raisedb
bytes_t smallpow2raisedb(bytes_t n, cntbit_t b){
    return ((n >> b) << b);
}
