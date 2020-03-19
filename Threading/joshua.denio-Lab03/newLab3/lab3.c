/*
Lab3
Author: Joshua DeNio
Date: 2/11/2020
Description: A program to calculate pi using MPI
*/

#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>
// Variables
const int MAX_NODES = 1024;
//long long n;
//double sum;
//double localSum;
//int source;

// Function on each node
double NodeSum(int comm_sz, int rank, int n);

//Functions to be executed by node 0
double Serial_pi(long long n);

int main(int argc, char* argv[]) {


   int n;
   double sum;
   double localSum;
   int source;

   //Set variables for rank, com size, and localN
   int my_rank, comm_sz;

   /* Let the system do what it needs to start up MPI */
   MPI_Init(&argc, &argv);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   /* Find out how many processes are being used */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   //Get the n value from the command line */
   n = strtoll(argv[1], NULL, 10);
   //printf("With n = %lld n has been set,\n", n);// used to test n

   //Set sum and localSum to 0
   sum = 0.0;                                                                                                              //localSum = 0.0;

   // Set localSum to its local value
   localSum = NodeSum(comm_sz, my_rank, n);

   if (my_rank != 0)
   {
      //Send the localSum to node 0
      MPI_Send(&localSum, 1, MPI_DOUBLE, 0, 0,
            MPI_COMM_WORLD);
   }

   /* Print the result */
   if (my_rank == 0) {

      //Get sum from nodes
      for (source = 1; source < comm_sz; source++)
      {
         MPI_Recv(&localSum, 1, MPI_DOUBLE, source, 0,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            //Add localSum to sum
            sum += localSum;
      }

      //Update sum * 4
      sum = 4.0 * sum;
	  
	  sum = sum/3.0;

      printf("With n = %d terms,\n", n);
      printf("   Our estimate of pi = %.15f\n", sum);
      sum = Serial_pi(n);
      printf("   Single node estimate  = %.15f\n", sum);
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
   
   
//printf("Rank %d myN = %lld\n", rank, my_n);


   // Check if my_first_i is even or odd and set factor
//   if (my_first_i % 2 == 0)
//      factor = 1.0;
//   else
//      factor = -1.0;

//   printf("Final %d factor = %f\n", rank, factor);

//   for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
//      localSum += factor/(2*i+1);
   //printf("%d local sum = %f\n", rank, localSum);
//  }
//  printf("Final %d local sum = %f\n", rank, localSum);

   return my_n * lSum;
}


/*
Name: Serial_pi
Input: long long
Output: double
Preconditions: none
Postconditions: none
*/
double Serial_pi(long long n)
{
   double sum = 0.0;
   long long i;
   double factor = 1.0;

   for (i = 0; i < n; i++, factor = -factor) {
      sum += factor/(2*i+1);
   }
   return 4.0*sum;

}
                      