#include "math_functions.h"
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

/**
 * Divides two integers.
 * @param a The numerator.
 * @param b The denominator.
 * @return The result of the division or an error message.
 */
double divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero\n");
        return 0.0;
    }
    return (double)a / b;
}
