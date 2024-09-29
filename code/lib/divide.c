#include "math_functions.h"
#include <stdio.h>

double divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero\n");
        return 0.0;
    }
    return (double)a / b;
}