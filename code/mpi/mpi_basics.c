#include <mpi.h>
#include <stdio.h>

#define DEBUG 1

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv); // Initialize the MPI environment

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // Get the number of processes

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Get the rank of the process

    // some debug info
    #ifdef DEBUG
        if (world_rank == 0) {
            int mpi_version, mpi_subversion;
            MPI_Get_version(&mpi_version, &mpi_subversion);
            printf("MPI library version: %d.%d\n", mpi_version, mpi_subversion);
            printf("Compiled with C standard: %ld\n", __STDC_VERSION__);
            int initialized, finalized;
            MPI_Initialized(&initialized);
            MPI_Finalized(&finalized);
            printf("MPI_Initialized: %d\n", initialized);
            printf("MPI_Finalized: %d\n", finalized);
            
            printf("Size of MPI_Comm: %zu bytes\n", sizeof(MPI_Comm));
            printf("Size of MPI_Datatype: %zu bytes\n", sizeof(MPI_Datatype));
        }
        MPI_Barrier(MPI_COMM_WORLD);
    #endif

    printf("Hello from process %d of %d\n", world_rank, world_size);

    MPI_Finalize(); // Finalize the MPI environment
    return 0;
}