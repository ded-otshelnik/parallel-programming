#include <stdio.h>

// macros for getting length of array
#define length(array) (sizeof(array) / sizeof(*array))

void func_ptr(int* arr, int len){
    printf("\nPassing array by pointer\n");
    for (int i = 0; i < len; i++){
        // address arithmetic 
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

void func_arr(int arr[], int len){
    printf("\nPassing array by value\n");
    for (int i = 0; i < len; i++){
        // usual access operation to array element
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // get length by macros and sizeof
    int len = length(numbers);
    printf("length = %d\n", len);

    // hack how to get length via address arithmetic
    // &numbers -> pointer to an array
    // (&numbers + 1) -> pointer ahead of the array
    // *(&numbers + 1) - numbers -> difference between start and end of the array
    printf("length = %d\n",(int) (*(&numbers + 1) - numbers));

    // calls are the same but passing is different
    func_arr(numbers, len);
    func_ptr(numbers, len);

    return 0;
}