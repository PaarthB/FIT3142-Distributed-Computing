#include "mpi.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/times.h>
#include <unistd.h>
#include <math.h>
#define ROOT 0

int main(int argc, char * argv[]){

  // setup timer - traditional way
  // struct tms before, after;

  int rank, size, interval;
  double pi_result, local_pi, start_time, finish_time;
  double PI25DT =  3.141592653589793238462643;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  while(1){

    if(rank == ROOT){
      printf("enter the number of intervals: "); 
      fflush(stdout);
      scanf("%d", &interval);
      fflush(stdin);
    }

    start_time = MPI_Wtime();
    MPI_Bcast(&interval, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
    if(interval <= 0){
        break;
    }

    double local_sum, height;
    int i;

    local_sum = 0.0;
    height = 1.0 / (double) interval;

    for(i = rank+1 ; i <= interval; i += size){
      double x;
      x = height * ( (double) i - 0.5 );
      local_sum += 4.0 / (1.0 + x*x);
    }
    local_pi = height * local_sum;
    

    MPI_Reduce(&local_pi, &pi_result, 1, MPI_DOUBLE, MPI_SUM, ROOT, MPI_COMM_WORLD);

    if(rank == ROOT){
      printf("pi is approximately %.20f\n, Error is %.20f\n", pi_result, fabs(pi_result-PI25DT));
      fflush(stdout);

      finish_time = MPI_Wtime();
      printf("Time taken: %1.16f second(s)\n", finish_time - start_time);
      fflush(stdout);
    }
  }

  MPI_Finalize();
  return 0;
}
