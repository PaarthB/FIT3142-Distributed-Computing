#include <stdio.h>
#include "mpi.h"
int main(argc, argv)
int argc;
char **argv;
{   
   int rank, size;
   int root_process = 0;
   int value = 0;
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   while (value >= 0){
   	if(rank == root_process) {
            scanf("%i", &value);
            fflush(stdin);
      	}

	MPI_Bcast(&value, 1, MPI_INT, root_process, MPI_COMM_WORLD);
        printf("Value received %d in process %d of %d\n", value, rank, size);
   }
   MPI_Finalize();
   return 0;
}
