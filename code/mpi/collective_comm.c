#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

// Total number of elements
#define N 1000000

int main(int argc, char *argv[]) {
    double *x, *local_x, total_sum = 0.0, local_sum = 0.0;
    
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0) {
        // Allocate and initialize the array on the root process
        x = (double*)malloc(N * sizeof(double));
        for (int i = 0; i < N; i++) {
            x[i] = 1;
        }
    }

    local_x = (double*)malloc(N / world_size * sizeof(double));

    MPI_Scatter(x, N / world_size, MPI_DOUBLE,
          local_x, N / world_size, MPI_DOUBLE,
          0, MPI_COMM_WORLD);

    // Each process computes its local sum
    for (int i = 0; i < N / world_size; i++) {
        local_sum += local_x[i];
    }

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("Total sum: %.2f\n", total_sum);
    }
    
    free(local_x);
    if (world_rank == 0) {
        free(x);
    }

    MPI_Finalize();
    return 0;
}