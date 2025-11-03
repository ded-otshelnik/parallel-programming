#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank;
    int world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    // Partner process rank
    int partner_rank = world_size - world_rank - 1;
    
    int ping_pong_count = 0;

    MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
    printf("Process %d sent ping %d to process %d\n", world_rank, ping_pong_count, partner_rank);

    MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received ping %d from process %d\n", world_rank, ping_pong_count, partner_rank);

    // Increment the ping pong count before sending it back
    ping_pong_count++;

    MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
    printf("Process %d sent pong %d to process %d\n", world_rank, ping_pong_count, partner_rank);

    MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received pong %d from process %d\n", world_rank, ping_pong_count, partner_rank);

    // Final exchange to confirm completion
    ping_pong_count++;

    MPI_Sendrecv(&ping_pong_count, 1, MPI_INT, partner_rank, 0,
                 &ping_pong_count, 1, MPI_INT, partner_rank, 0,
                  MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d final ping pong count is %d\n", world_rank, ping_pong_count);

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}