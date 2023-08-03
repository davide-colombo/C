
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

    printf("\n<INTEGER LIMITS>\n");
    printf("INT8_MIN \t=\t %d\n", INT8_MIN);
    printf("INT8_MAX \t=\t %d\n", INT8_MAX);
    printf("INT16_MIN \t=\t %d\n", INT16_MIN);
    printf("INT16_MAX \t=\t %d\n", INT16_MAX);
    printf("INT32_MIN \t=\t %d\n", INT32_MIN);
    printf("INT32_MAX \t=\t %d\n", INT32_MAX);
    printf("INT64_MIN \t=\t %lld\n", INT64_MIN);
    printf("INT64_MAX \t=\t %lld\n", INT64_MAX);

    printf("\n");

    return 0;
}