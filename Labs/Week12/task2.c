#include "mpi.h"
#include <stdio.h>
#define ROOT 0

int main(int argc, char* argv[]){
  int rank, size, i, retrieved, send;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int process_no = 1;
  if(rank == ROOT){
    for(i = 0; i < 100 * (size-1); i++){
      if(process_no == size){
        process_no = 1;
      }
      MPI_Recv(&retrieved, 1, MPI_INT, process_no++, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      printf("Msg from %d with tag %d\n", status.MPI_SOURCE, status.MPI_TAG);
    }
  }
  else{
    send = 10;
    for(i = 0; i < 100; i++){
      MPI_Send(&send, 1, MPI_INT, 0, i, MPI_COMM_WORLD);
    }
  }
  MPI_Finalize();
  return 0;
}
