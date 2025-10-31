#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv); // Initialize the MPI environment

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Get the rank of the process

    int ping_pong_count = 0;
    int partner_rank = (world_rank + 1) % 2; // Partner process rank
    if (world_rank % 2 == 0) {
        // Process 0 starts the ping-pong
        MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
        printf("Process %d sent ping_pong_count %d to process %d\n", world_rank, ping_pong_count, partner_rank);
    }
    else if (world_rank % 2 == 1) {
        MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received ping_pong_count %d from process %d\n", world_rank, ping_pong_count, partner_rank);
    }

    MPI_Finalize(); // Finalize the MPI environment
    return 0;
}