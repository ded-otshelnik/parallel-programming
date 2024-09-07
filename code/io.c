#include <stdio.h>

int main(){
    // <----- console output ----- >
    // simple usage for integers

    int a = 1;
    printf("%d\n", a);

    // printf for floating point numbers

    float exp = 2.713;
    double pi = 3.1415926;

    printf("e = %.2f", exp);
    printf("pi = %.4f", pi);

    // <----- console input ----- >

    // declaration must be before 'scanf' call

    int first, second;
    printf("Enter first number: ");

    // it stores value
    // by appeal to memory address of variable

    scanf("%d", &first);

    printf("Enter second number: ");
    scanf("%d", &second);

    // printf can process the output
    // with almost infinite
    // amount of parameters

    printf("%d + %d = %d\n", first, second, first + second);

    return 0;
}