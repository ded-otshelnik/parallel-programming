#include <stdio.h>

// get value of variable from pointer
void func(int* ptr){
    printf("\nGetting value in function\n");
    printf("Value = %d, address = %p\n", *ptr, ptr);
}

int main(){
    // variable
    int var = 10;
    // pointer to variable
    int* ptr = &var;
    printf("Value = %d, address = %p\n", *ptr, ptr);

    printf("\nGet value by pointer\n");
    // variable initialized by value via pointer
    // but in another memory block
    int another_var = *ptr;
    printf("Value = %d, address = %p\n", var, &var);
    printf("Value = %d, address = %p\n", another_var, &another_var);

    // pointer can be used for passing variable to other functions
    func(ptr);

    printf("\nChange value of first variable\n");
    // change of first variable doesn't influence on second one
    // but pointer will reference to value 20
    var = 20;
    printf("Value (from variable) = %d, address = %p\n", var, &var);
    printf("Value (by pointer)    = %d, address = %p\n", *ptr, ptr);
    printf("Value = %d, address = %p\n", another_var, &another_var);

    printf("\nChange value via pointer\n");
    *ptr = 30;
    printf("Value (from variable) = %d, address = %p\n", var, &var);
    printf("Value (by pointer)    = %d, address = %p\n", *ptr, ptr);

    printf("\nPointer to pointer\n");
    int** ptr2ptr = &ptr;
    printf("Value = %p, address = %p\n", *ptr2ptr, ptr2ptr);
    printf("Value = %d, address = %p\n", *ptr, ptr);

    printf("\nRelations to variable\n");
    // it works because of double dereferencing
    **ptr2ptr = 1;
    printf("Value (from variable)     = %d, address = %p\n", var, &var);
    printf("Value (by pointer)        = %d, address = %p\n", *ptr, &ptr);    
    printf("Value (by double pointer) = %d, address = %p\n", **ptr2ptr, &ptr2ptr);    
    return 0;
}