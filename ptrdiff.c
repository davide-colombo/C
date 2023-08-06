
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

int main(int argc, char **argv){

    const size_t N = 100;
    int numbers[N];

    printf("PTRDIFF_MAX = %ld\n", PTRDIFF_MAX);
    int *p1 = &numbers[18];
    int *p2 = &numbers[23];

    ptrdiff_t diff = p2 - p1;
    printf("p2 - p1 = %td\n", diff);

    diff = p1 - p2;
    printf("p1 - p2 = %td\n", diff);

    return 0;
}