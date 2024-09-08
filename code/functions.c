#include <stdio.h>

// declaration before usage
double mean(int a, int b){
    return a + b / 2.0;
}

// declaration via prototype before usage and implementation
double garmonic(int a, int b);

// void function that returns nothing
void print_characteristics(int a, int b){
    // it works
    printf("Mean of %d and %d is %f", a, b, mean(a, b));
    // it also will work
    printf("Garmonic of %d and %d is %f", a, b, garmonic(a, b));
}

/**
 * @brief Main part of program
 * 
 * @return int 
 */
int main(){
    int a = 10;
    int b = 11;
    print_characteristics(a, b);
    return 0;
}

// implementation of function after formal declaration
double garmonic(int a, int b){
    return a + b / 2.0;
}