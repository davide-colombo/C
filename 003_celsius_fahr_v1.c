
#include <stdio.h>

main(){

    float fahr, celsius;
    int lower, upper, step;

    lower = 1;
    upper = 300;
    step = 15;

    printf("C°\tF°\n");

    celsius = lower;
    while(celsius <= upper){
        fahr = (9.0 / 5.0) * celsius + 32.0;
        printf("%3.0f %6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}