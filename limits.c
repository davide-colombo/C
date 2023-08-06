
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int main(){

    char ic;
    short is;
    int ii;
    long il;
    long long ill;

    float ff;
    double fd;

    void *ptr;

    printf("<INTEGERS>\n");
    printf("sizeof char \t=\t %zu bytes\n", sizeof(ic));
    printf("sizeof short \t=\t %zu bytes\n", sizeof(is));
    printf("sizeof int \t=\t %zu bytes\n", sizeof(ii));
    printf("sizeof long \t=\t %zu bytes\n", sizeof(il));
    printf("sizeof llong \t=\t %zu bytes\n", sizeof(ill));
    printf("\n<FLOATING POINT>\n");
    printf("sizeof float \t=\t %zu bytes\n", sizeof(ff));
    printf("sizeof double \t=\t %zu bytes\n", sizeof(fd));
    printf("\n<MEMORY ADDRESS>\n");
    printf("sizeof void* \t=\t %zu bytes\n", sizeof(ptr));

    printf("\n<SIGNED INTEGER LIMITS>\n");
    printf("INT8_MIN \t=\t %d\n", INT8_MIN);
    printf("INT8_MAX \t=\t %d\n", INT8_MAX);
    printf("INT16_MIN \t=\t %d\n", INT16_MIN);
    printf("INT16_MAX \t=\t %d\n", INT16_MAX);
    printf("INT32_MIN \t=\t %d\n", INT32_MIN);
    printf("INT32_MAX \t=\t %d\n", INT32_MAX);
    printf("INT64_MIN \t=\t %lld\n", INT64_MIN);
    printf("INT64_MAX \t=\t %lld\n", INT64_MAX);

    // https://en.cppreference.com/w/c/types/limits
    printf("\n<SIGNED NUMERIC LIMITS>\n");
    printf("CHAR_BIT \t=\t %d\n", CHAR_BIT);
    printf("CHAR_MIN \t=\t %d\n", CHAR_MIN);
    printf("CHAR_MAX \t=\t %d\n", CHAR_MAX);
    printf("SCHAR_MIN \t=\t %d\n", SCHAR_MIN);
    printf("SCHAR_MAX \t=\t %d\n", SCHAR_MAX);
    printf("SHRT_MIN \t=\t %d\n", SHRT_MIN);
    printf("SHRT_MAX \t=\t %d\n", SHRT_MAX);
    printf("INT_MIN \t=\t %d\n", INT_MIN);
    printf("INT_MAX \t=\t %d\n", INT_MAX);
    printf("LONG_MIN \t=\t %ld\n", LONG_MIN);
    printf("LONG_MAX \t=\t %ld\n", LONG_MAX);
    printf("LLONG_MIN \t=\t %lld\n", LLONG_MIN);
    printf("LLONG_MAX \t=\t %lld\n", LLONG_MAX);

    printf("\n<UNSIGNED NUMERIC LIMITS>\n");
    printf("UCHAR_MAX \t=\t %u\n", UCHAR_MAX);
    printf("USHRT_MAX \t=\t %u\n", USHRT_MAX);
    printf("UINT_MAX \t=\t %u\n", UINT_MAX);
    printf("ULONG_MAX \t=\t %lu\n", ULONG_MAX);
    printf("ULLONG_MAX \t=\t %llu\n", ULLONG_MAX);

    printf("\n<OTHER NUMERIC LIMITS>\n");
    printf("PTRDIFF_MIN \t=\t %td\n", PTRDIFF_MIN);
    printf("PTRDIFF_MAX \t=\t %td\n", PTRDIFF_MAX);
    printf("SIZE_MAX \t=\t %zu\n", SIZE_MAX);


    printf("\n");

    return 0;
}