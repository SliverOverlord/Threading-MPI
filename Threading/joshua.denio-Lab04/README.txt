Author: Joshua DeNio
Date: 2/18/2020
Program: lab4 mpi_pi 1 and 2

This program is suposed to calculate pi over nodes using MPI. 
Pi is calculated using n terms where n is entered as user input mpi_pi1 uses send and recV while mpi_pi2 uses Bcast.

Known bugs: 

To compile the first program cd to the correct folder.
Then enter: mpicc -g -Wall -o mpi_pi1 mpi_pi1.c
To run the program: enter mpiexec -n <number of nodes> ./mpi_pi1 
	Then enter n as user input.
Example: mpiexec -n 4 ./mpi_pi1

To compile the second program cd to the correct folder.
Then enter: mpicc -g -Wall -o mpi_pi2 mpi_pi2.c
To run the program: enter mpiexec -n <number of nodes> ./mpi_pi2
	Then enter n as user input.
Example: mpiexec -n 4 ./mpi_pi2

Below are some test runs

denio@lab18:~/Documents/lab4$ mpicc -g -Wall -o mpi_pi1 mpi_pi1.c
denio@lab18:~/Documents/lab4$ mpiexec -n 4 ./mpi_pi1
Enter a value for n:
100000
With n = 100000 terms,
   Our estimate of pi = 3.141592653598117
                   pi = 3.141592653589793
denio@lab18:~/Documents/lab4$ mpiexec -n 4 ./mpi_pi1
Enter a value for n:
1000000
With n = 1000000 terms,
   Our estimate of pi = 3.141592653589903
                   pi = 3.141592653589793
denio@lab18:~/Documents/lab4$

-------------------------------------------------

denio@lab18:~/Documents/lab4$ mpicc -g -Wall -o mpi_pi2 mpi_pi2.c
denio@lab18:~/Documents/lab4$ mpiexec -n 4 ./mpi_pi2
Enter a value for n:
100000
With n = 100000 terms,
   Our estimate of pi = 3.141592653598117
                   pi = 3.141592653589793
denio@lab18:~/Documents/lab4$ mpiexec -n 4 ./mpi_pi2
Enter a value for n:
1000000
With n = 1000000 terms,
   Our estimate of pi = 3.141592653589903
                   pi = 3.141592653589793
denio@lab18:~/Documents/lab4$