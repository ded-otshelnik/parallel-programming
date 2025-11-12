#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

// Total number of elements
const int N = 120000;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int *data = NULL;
    int elements_per_proc = N / world_size;
    int *sub_data = (int*)malloc(elements_per_proc * sizeof(int));

    if (world_rank == 0) {
        data = (int*)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            data[i] = i;
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Scatter(data, elements_per_proc, MPI_INT, sub_data, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process prints its received sub-array
    printf("Process %d received: ", world_rank);
    for (int i = 0; i < elements_per_proc; i++) {
        sub_data[i] = sub_data[i] * 2;
    }
    printf("\n");

    // Gather the sub-arrays back to the root process
    int *gathered_data = NULL;
    if (world_rank == 0) {
        gathered_data = (int*)malloc(N * sizeof(int));
    }

    MPI_Gather(sub_data, elements_per_proc, MPI_INT, gathered_data, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("Gathered data: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", gathered_data[i]);
        }
        printf("\n");
        free(data);
        free(gathered_data);
    }

    free(sub_data);
    MPI_Finalize();
    return 0;
}