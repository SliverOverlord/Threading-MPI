//Author: Joshua DeNio
//Date: 7/22/2019
//Description: This program creates a matrix and splits
// the matrix between several client machines to test mpi functionalit    y. It then uses reduce to reduce the segments
# include <math.h>
# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
#include <string.h>

int main ( int argc, char *argv[] );

//Method name: makeMatrix
//Description: creates a matrix
//Input: int row, int col, int* matrix
//Output: void
//Preconditions: int* must be declared.
//Postconditions: A matrix is created.
void makeMatrix(int row, int col, int* matrix);

//Method name: split
//Description: splits the matrix and sends the segments
//Input: int, row, int col, int* matrix, int ierr, int tag
//Output: void
//Preconditions: There must be a valid matrix.
//Postconditions: Matrix segments sent to the clients.
void split(int row, int col, int* matrix, int ierr, int tag);
 
//Method name: printMatrix
//Description: prints the matrix to terminal
//Input: int row, int col, int* matrix
//Output: void
//Preconditions: must have a valid matrix and int vals
//Postconditions: A matrix is printed to the terminal.
void printMatrix(int row, int col, int* matrix);

//Method name: reduceMatrix
//Description:
//Input:
//Output:
//Preconditions:
//Postconditions:


void makeMatrix(int row, int col, int* matrix){
      for(int i=0; i< row*col; i++){
          // matrix[i] = i + 1;
          matrix[i] = rand() % 100 +1;
       }
  }
 
void printMatrix(int row, int col, int* matrix){
//for(int i = 0; i < sizeof(matrix); i++){
      for(int i = 0; i < row*col; i++){
          printf("%d",matrix[i]);
          printf("\n");
      }
  }

int main ( int argc, char *argv[] ){

     //pointer to the matrix
     int *a;
     //pointer to the segment
     int *a_segment;

     //destination
     int dest;

     int ierr;
     //row count
     int row = 4;
     //columns
     int col = 4;

     //number of elements in the array
     int arraySize = row * col;

     //total
     int total = 0;

     //set master = 0
     int master = 0;

     //rank
     int my_rank;
     //size
     int num_procs;

     //number of segments will be used later
     int num_segments;
     //number of clients
     int num_workers;

     //status
     MPI_Status status;

     //the tag
     int tag = 0;


ierr = MPI_Init ( &argc, &argv );

     ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );

     ierr = MPI_Comm_size ( MPI_COMM_WORLD, &num_procs );

     if ( my_rank == 0 ) {
       printf("The master is here\n");

       printf("The total is: %d\n",total);

       a = (int *) malloc (row * col * sizeof(int));

       //populate the matrix
       makeMatrix(row,col,a);

       //print the matrix
       printf("The original matrix is:\n");
       printMatrix(row,col,a);
     }
     else{
         a_segment = (int *) malloc (row * col * sizeof(int));
     }

if (my_rank == 0){
         num_segments = 0;

         //split the matrix
         //split(r,c,a,ierr,tag);

         int *first;
         int *last;

         int l = (row * col);

         first = (int *) malloc (row * col * sizeof(int));
         last = (int *) malloc (row * col * sizeof(int));

         memcpy(first, a, 8 * sizeof(int));
         memcpy(last, a+8, 8 * sizeof(int));

         ierr = MPI_Send( first, row*col, MPI_INT, 1, tag, MPI_COMM_WORLD );
         //send the last segment
         ierr = MPI_Send( last, row*col, MPI_INT, 2, tag, MPI_COMM_WORLD );
         //free memory
         free(a);
         a = NULL;
         free(first);
         first = NULL;
         free(last);
         last = NULL;

     }

else{
         ierr = MPI_Recv(a_segment, row*col, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
         //set row and arraySize to new segment size
         row = row/2;
         arraySize = row*col;

         printf("--------------------------------\n");
         printf("Client %d recived a matrix segment:\n\n", my_rank);
	 
	 printMatrix(row,col,a_segment);
         printf("Reducing:\n");
         //MPI_Send( a_segment, row*col, MPI_INT, 0, 1, MPI_COMM_WORLD );

	MPI_Reduce(a_segment, &total, row*col, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	//free memory
         free(a_segment);
         a_segment = NULL;
     }

if(my_rank == 0){
	MPI_Reduce(a_segment, &total,row*col,  MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	printf("\nAfter reduce the total is: %d\n",total);
}

ierr = MPI_Finalize();
return 0;
}
