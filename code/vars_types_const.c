#include <stdio.h>
// const using #define
#define DEF_CONST 0
// const within function
const int global_const = 0;
// enumeration (set of constants)
enum ENUM_CONSTANTS {NIL, ONE, TWO};

int main(){
    // variables

    // integers
    short short_var = 1;
    int int_var = 1;
    long long_var = 1l;
    long long ll_var = 1LL;
    unsigned int uint_var = 1;

    // type convert of integers

    int_var = (int) uint_var;
    int_var = (int) ll_var;

    // floating point numbers
    float f_var = 1.f;
    f_var = 1.0f;

    double d_var = 1.;
    d_var = 1.0;
    long double lld_var = 1.;

    // type convert of float and double
    d_var = (double) f_var;
    f_var = (float) d_var;

    // characters
    char ch = 'a';
    
    // constants

    // const within function
    const int func_const = 0;
    // enum variable
    enum ENUM_CONSTANTS enum_const = NIL;
    // all calls print the same
    printf("Using #define: %d\n",         DEF_CONST);
    printf("Using global variable: %d\n", global_const);
    printf("Using local variable: %d\n",  func_const);
    printf("Using enum value: %d\n",      NIL);
    printf("Using enum variable: %d\n",   enum_const);
    return 0;
}