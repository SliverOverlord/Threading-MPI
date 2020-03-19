*
Author: Joshua DeNio
Date:   03/09/2020

Program: Assignment02
Description: 

To compile: g++ -O3 -w joshua.denioAssig2.cpp -lpthread -o joshua.denioAssig2
To run: ./joshua.denioAssig2 filename n

example:
./joshua.denioAssig2 toyGraph1.txt 4
note: n is the number of threads.
*/

Known bugs: none

Example output:

denio@lab18:~/Documents/CSCI615/denioAssignment2$ g++ -O3 -w joshua.denioAssig2.cpp -lpthread -o joshua.denioAssig2
denio@lab18:~/Documents/CSCI615/denioAssignment2$ ./joshua.denioAssig2 HcNetwork.txt 1
Graph has 4009 nodes
Time elapsed: 0.0510089
The clustering coefficient of the graph is: 0.16402
denio@lab18:~/Documents/CSCI615/denioAssignment2$ ./joshua.denioAssig2 HcNetwork.txt 2
Graph has 4009 nodes
Time elapsed: 0.038393
The clustering coefficient of the graph is: 0.16402
denio@lab18:~/Documents/CSCI615/denioAssignment2$ ./joshua.denioAssig2 HcNetwork.txt 4
Graph has 4009 nodes
Time elapsed: 0.027009
The clustering coefficient of the graph is: 0.16402
denio@lab18:~/Documents/CSCI615/denioAssignment2$ ./joshua.denioAssig2 HcNetwork.txt 8
Graph has 4009 nodes
Time elapsed: 0.018913
The clustering coefficient of the graph is: 0.16402
denio@lab18:~/Documents/CSCI615/denioAssignment2$ ./joshua.denioAssig2 HcNetwork.txt 16
Graph has 4009 nodes
Time elapsed: 0.013592
The clustering coefficient of the graph is: 0.16402

-----------------------------------------------------------------------

denio@lab18:~/Documents/CSCI615/denioAssignment2$ ./joshua.denioAssig2 graphV30000.txt 1
Graph has 30000 nodes
Time elapsed: 1229.84
The clustering coefficient of the graph is: 0.049979

denio@lab10:~/Documents/CSCI615/denioAssignment2$ ./joshua.denioAssig2 graphV30000.txt 2
Graph has 30000 nodes
Time elapsed: 737.985
The clustering coefficient of the graph is: 0.049979

denio@lab11:~/Documents/CSCI615/denioAssignment2$ ./joshua.denioAssig2 graphV30000.txt 4
Graph has 30000 nodes
Time elapsed: 379.305
The clustering coefficient of the graph is: 0.049979

denio@lab18:~/Documents/CSCI615/denioAssignment2$ ./joshua.denioAssig2 graphV30000.txt 8
Graph has 30000 nodes
Time elapsed: 258.843
The clustering coefficient of the graph is: 0.049979

denio@lab11:~/Documents/CSCI615/denioAssignment2$ ./joshua.denioAssig2 graphV30000.txt 16
Graph has 30000 nodes
Time elapsed: 289.034
The clustering coefficient of the graph is: 0.049979