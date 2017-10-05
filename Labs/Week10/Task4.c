#include <stdio.h>
#include <stddef.h>
#include "mpi.h"



int main(argc, argv)
int argc;

char **argv;
{   
   struct {
	int a; 
        double b;
   } new_vals;
   int rank, size;
   int root_process = 0;
   int value = 0;
   //double db;
   int a;
   double b;
   char packbuf[100];
   int position;
   int len[2] = {1, 1};
   
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Datatype newType;
   MPI_Datatype oldTypes[2] = {MPI_INT, MPI_DOUBLE};
   MPI_Aint offsets[2];
   MPI_Address(&new_vals.a, &offsets[0]);
   MPI_Address(&new_vals.b, &offsets[1]);
   offsets[1] = offsets[1] - offsets[0];
   offsets[0] = 0;

   //offsets[0] = offsetof(new_vals, a);
   //offsets[1] = offsetof(new_vals, b);
   MPI_Type_struct(2, len, offsets, oldTypes, &newType );
   MPI_Type_commit(&newType);
   while (value >= 0){
   	if(rank == root_process) {
            scanf("%d %lf", &a, &b);
            value = a;
            position = 0; 
  	    MPI_Pack(&a, 1, MPI_INT, packbuf, 100, &position, MPI_COMM_WORLD); 
  	    MPI_Pack(&b, 1, MPI_DOUBLE, packbuf, 100, &position, MPI_COMM_WORLD); 
            
            fflush(stdin); 
      	}

        MPI_Bcast(&packbuf, 1, newType, 0, MPI_COMM_WORLD);

        if (rank != root_process){
	   position = 0;
           MPI_Unpack(&packbuf, 100, &position, &a, 1, MPI_INT, MPI_COMM_WORLD);
           MPI_Unpack(&packbuf, 100, &position, &b, 1, MPI_DOUBLE, MPI_COMM_WORLD);
        }
        printf("Integer: %d Double: %lf in process %d of %d\n", a, b, rank, size);
   }
   MPI_Finalize();
   return 0;
}

