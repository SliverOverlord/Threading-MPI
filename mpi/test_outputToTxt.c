/*
Name: Joshua DeNio

*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MASTER 0

int main(int argc, char* argv[])
{
	int world_rank, world_size;
	size_t arr_size;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	
	

	
    if (world_rank != MASTER)
    {
        FILE * fp;
        
        int i;
        
        fp = fopen ("output.txt","w");
        
        fprintf( fp, "Stuff in file");
        
        fclose (fp);
        
    }
    
    if (world_rank == MASTER)
	{
		printf("Operation has been completed!\n");
		
	}

	MPI_Finalize();
}

