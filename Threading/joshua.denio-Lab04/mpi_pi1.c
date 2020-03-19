/*
Lab4
Author: Joshua DeNio
Date: 2/11/2020
Description: Lab4 is a program to calculate pi using MPI
*/

#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>

// Function on each node
double NodeSum(int comm_sz, int rank, int n);

int main(int argc, char* argv[]) {


   int n;
   double sum;
   double localSum;

   //Set variables for rank, com size, and localN
   int my_rank, comm_sz;

   /* Let the system do what it needs to start up MPI */
   MPI_Init(&argc, &argv);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   /* Find out how many processes are being used */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   if (my_rank == 0)
   {
      //Get the n value from the user
      printf("Enter a value for n:\n");
      scanf("%d", &n);

      //Send n to all nodes
      for (int i = 1; i < comm_sz; i++)
      {
         MPI_Send(&n, 1, MPI_INT, i, 0,
            MPI_COMM_WORLD);
      }
   }
   if (my_rank != 0)
   {
       //get n from node 0
       MPI_Recv(&n, 1, MPI_INT, 0, 0,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   }
   
   
   //Set sum to 0
   sum = 0.0;
   // Set localSum to its local value
   localSum = NodeSum(comm_sz, my_rank, n);

   MPI_Reduce(&localSum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

   /* Print the result */
   if (my_rank == 0) {

      //Print output
      printf("With n = %d terms,\n", n);
      printf("   Our estimate of pi = %.15f\n", sum);
      printf("                   pi = %.15f\n", 4.0*atan(1.0));
   }

   /* Shut down MPI */
   MPI_Finalize();

   return 0;
} /*  main  */

/*------------------------------------------------------------------
 Name: Node_sum
 Input: void* rank
 Output: none
 Preconditions:
 Postconditions:
 */
double NodeSum(int comm_sz, int rank, int n)
{
   double lSum = 0.0;
   double my_rank = (double)rank;
//   double factor;
   double x;
//   double i;
   int i;
   double my_n = 1.0 / (double)n;
//   double my_first_i = my_n*my_rank;
//   double my_last_i = my_first_i + my_n;

   for( i = my_rank + 1; i <= n; i += comm_sz)
   {
     x = my_n * ((double)i - 0.5);
     lSum += 4.0 / (1.0 + x*x);
   }

   return my_n * lSum;
}
                      