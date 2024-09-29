#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, M;
    printf("Enter the size of the matrix\nNumber of rows: ");
    scanf("%d", &N);
    printf("Number of colums: ");
    scanf("%d", &M);

    // here we allocate memory for the matrix
    // using calloc because it initializes the memory to 0
    // and it is faster and easier to understand than malloc
    int** matrix = (int**) calloc(N, sizeof(int*));
    for(int i = 0; i < N; i++){
        matrix[i] = (int*) calloc(M, sizeof(int));
    }   
    printf("Matrix is allocated\nInitializing matrix...\n");

    // standard way to initialize a matrix
    // is using two for loops
    // and filling the matrix with random numbers
    // formula for range of nums:
    // rand() % (MAX_VALUE - MIN_VALUE) + MIN_VALUE
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            matrix[i][j] = rand() % 100;
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // deallocate memory in similar way
    // as we allocated it
    for (int i = 0; i < N; i++){
        free(matrix[i]);
    }
    // free the memory allocated for the pointers
    free(matrix);

    printf("Matrix is deallocated\n");
    return 0;
}