#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main( argc, argv )
int argc;
char **argv;
{

   MPI_Comm newcomm;
   MPI_Status status;
   int rank, value, size;
   static const int dims [] = {4}, periodic [] = {1} , reorder = 0;
   int error;
   int coord[2], id;
   int up, down, right, left;
   MPI_Init(&argc, &argv);
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   MPI_Comm_size( MPI_COMM_WORLD, &size );
   //printf("%d\n", size);
   MPI_Cart_create(MPI_COMM_WORLD, 1, dims, periodic, reorder, &newcomm);
   
   do {
      MPI_Cart_coords(newcomm, rank, 2, coord);
      //fflush(stdout);
      if (rank == 0){
          fscanf(stdin, "%d", &value );
          MPI_Cart_shift(newcomm, 1, 1, &left, &right);
          //printf("%d %d\n", left, right);
          MPI_Send( &value, 1, MPI_INT, right, 0, newcomm );
      }

      else {
         MPI_Cart_shift(newcomm, 0, 1, &left, &right);
         //fflush(stdout);
         //printf("%d %d\n", left, right);
	 MPI_Recv( &value, 1, MPI_INT, left, 0, newcomm, &status);
	 if (rank < size - 1) 
            MPI_Send( &value, 1, MPI_INT, right, 0, newcomm );
      }
      printf("Process %d got %d\n", rank, value );
      //fflush(stdout);
   } while (value >= 0);

   MPI_Finalize();
   
   return 0;
}
