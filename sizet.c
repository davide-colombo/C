
#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv){

    const size_t N = 100;
    int numbers[N];

    for(size_t i = 0; i < N; ++i)
        numbers[i] = i;
    
    printf("SIZE_MAX = %zu\n", SIZE_MAX);

    size_t size = sizeof numbers;
    printf("size = %zu\n", size);

    return 0;
}