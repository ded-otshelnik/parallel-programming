#include <stdio.h>

#define length(array) (sizeof(array) / sizeof(*(array)))

int main(){
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    size_t len = sizeof(numbers) / sizeof(int);

    printf("%zu\n", len);
    return 0;

    
}