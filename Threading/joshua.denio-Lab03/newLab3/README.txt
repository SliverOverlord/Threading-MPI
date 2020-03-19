Author: Joshua DeNio
Date: 2/18/2020
Program: lab3

This program is suposed to calculate pi over nodes using MPI. 
Pi is calculated using n terms where n is entered as a command line arg during execution.

Known bugs: none Bugs have been fixed

To compile the program cd to the correct folder.
Then enter: mpicc -g -Wall -o lab3 lab3.c
To run the program: enter mpiexec -n <number of nodes> ./lab3 <number for n>
Example: mpiexec -n 4 ./lab3 1000000

Below are some test runs

denio@lab18:~/Documents/lab3$ denio@lab18:~/Documents/lab3$ mpicc -g -Wall -o lab3 lab3.c
denio@lab18:~/Documents/lab3$ mpiexec -n 4 ./lab3 1000000
With n = 1000000 terms,
   Our estimate of pi = 3.141591653590266
   Single node estimate  = 3.141591653589774
                   pi = 3.141592653589793
denio@lab18:~/Documents/lab3$ mpiexec -n 4 ./lab3 100000
With n = 100000 terms,
   Our estimate of pi = 3.141582653631449
   Single node estimate  = 3.141582653589720
                   pi = 3.141592653589793
denio@lab18:~/Documents/lab3$ mpiexec -n 4 ./lab3 10000
With n = 10000 terms,
   Our estimate of pi = 3.141492657755000
   Single node estimate  = 3.141492653590034
                   pi = 3.141592653589793
denio@lab18:~/Documents/lab3$  