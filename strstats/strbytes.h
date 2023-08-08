
#ifndef STRBYTES_H_INCLUDED
#define STRBYTES_H_INCLUDED

#include <stddef.h>
#include <stdint.h>

// opaque data for byte manipulation
typedef size_t bytes_t;

// opaque data for bit count
typedef uint32_t cntbit_t;

cntbit_t countbits(bytes_t n);
bytes_t smallpow2raisedb(bytes_t n, cntbit_t b);

#endif
