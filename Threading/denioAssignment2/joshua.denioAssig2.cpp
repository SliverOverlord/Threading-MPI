/*
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

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>
#include "timer.h"

using namespace std;

typedef vector<vector<int> > AdjacencyMatrix;

// Variable declarations
const int MAX_THREADS = 1024;
long thread_count;
// Mutex m
pthread_mutex_t lockM;

AdjacencyMatrix adjMatrix;
AdjacencyMatrix adjList;

int n;
double sum = 0;

//  Function declarations ****************

// Function name: printAdjMatrix()
// Input: none
// Output: none
// Precondition: Must have a valid matrix
// Postcondition: Matrix will be printed
void printAdjMatrix();

// Function name: printAdjList()
// Input: none
// Output: none
// Precondition: mMust have a valid list
// Postcondition: List will be printed
void printAdjList();

// Function name: calculateCC()
// Input: int x
// Output: double
// Precondition: Must have valid data
// Postcondition: none
double calculateCC(int x);

// Function name: thread_work
// Input: void* rank
// Output: none
// Precondition: Must have valid data
// Postcondition: Threads work on their sections and update sum.
void* thread_work(void* rank);

// End function declairations ***************

void printAdjMatrix()
{
    for (int i=0; i<adjMatrix.size(); i++)
    {
        for (int j=0; j<adjMatrix[i].size(); j++) 
	    cout<<adjMatrix[i][j]<<" ";

        cout<<endl;
    }

}

void printAdjList()
{
    cout<<"Printing AdjList"<<endl;
    for (int i=0; i<adjList.size(); i++)
    {
        cout<<"Neighbors of node "<<i <<" :: ";
        for (int j=0; j<adjList[i].size(); j++) 
	    cout<<adjList[i][j]<<" ";

        cout<<endl;
    }

}


// double calculateCC(int x)
// {
// 	//Calculate CC for node i

//     // Number of connections
// 	double local_sum = 0.0;
    
//     int nn = adjList[x].size();
    
//     if ( nn < 2 )
//     {
//         return 0;
//     }

    
//     for (int i = 0; i < nn; i++)
//     {
//         int rel = 0;
//         int u = adjList[x][i];
//         for ( int j = 0; j < x; j++ )
//         {
//             int v = adjList[x][j];
            
//         }
//     }

//     // Update sum
//     return local_sum;
   
// }

void* thread_work(void* rank)
{
    // cast the rank to a long
    long my_rank = (long) rank;

    long long my_n = n/thread_count;

    // Start and end possitions for each thread
    long long my_start = my_n * my_rank;
    long long my_end = (my_start + my_n);

    // Number of connections locally
	double local_sum = 0.0;

    // If the data can be evenly spread spread it or send the extra to the last thread
    if (my_rank == thread_count - 1)
    {
        my_end = (n % thread_count) + my_end ;
    }
    if (adjList.size() < 10)
    {
        cout << "my rank" << my_rank << endl;
        cout << "start: "<< my_start << " end: "<< my_end << " my_n: " << my_n<< endl;
    }

    for (int i = my_start; i < my_end; i++ )
    {
        // Set a counter for the number of friends
        double count = adjList[i].size();
        count = count* (count - 1)/2;
       
        // rel holds the number of relationships
        double rel = 0.0 ;

        for (int j = 0; j < n ; j++)
        {
               
            if (i != j && adjMatrix[i][j] == 1)
            {
                for (int k = 0; k < n; k++)
                {
                    if (adjMatrix[i][k] == 1 && adjMatrix[j][k] == 1)
                    {
                        rel += 1;          
                    }
                }
            }
        }
        // Dont / by 0
        if (count != 0)
        {
            rel = rel/2;
            //Set local_sum
            local_sum += (rel/count);
        }
    }

    // Lock mutex, increment count and unlock
   pthread_mutex_lock(&lockM);
   sum += local_sum;
   pthread_mutex_unlock(&lockM);

}

int main(int argc, char** argv)
{
	if(argc<2){
      cout<<"To run: ./joshua.denioAssig2 filename"<<endl;
      cout<<"./joshua.denioAssig2 toyGraph1.txt"<<endl;
      return 0;
    }
	
	// Declarations for threads.
    long thread;
    pthread_t* thread_handles;

	
	// Doubles for the timer
    double start, finish, elapsed;
	
	thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
	
	// Read input file name
    fstream myFile(argv[1], std::ios_base::in);

    // Variables set n from cmd line arg.
    thread_count = atoi(argv[2]);
    int u;
    int v;
    
    int maxNode = 0;

    vector<pair<int,int> > allEdges;
    while(myFile >> u >> v)
    {
        allEdges.push_back(make_pair(u,v));
        if(u > maxNode)
          maxNode = u;

        if(v > maxNode)
          maxNode = v;                 
    }

    n = maxNode +1;  //Since nodes starts with 0
    cout<<"Graph has "<< n <<" nodes"<<endl;

    adjMatrix = AdjacencyMatrix(n,vector<int>(n));
    adjList = AdjacencyMatrix(n,vector<int>());
    //populate the matrix
    for(int i = 0; i<allEdges.size() ; i++){
       u = allEdges[i].first;
       v = allEdges[i].second;
       adjMatrix[u][v] = 1;
       adjMatrix[v][u] = 1;
       adjList[u].push_back(v);
       adjList[v].push_back(u);
    }
   
    if(n<=10){ 
      printAdjMatrix();
      printAdjList();
    }



    // Line to set up start
    GET_TIME(start);

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread], NULL, thread_work, (void*)thread);
    }

    // Join the threads
    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread], NULL);
    }

    // Finished timeing
    GET_TIME(finish);

    // Set time elapsed
    elapsed = finish - start;

    // Print time elapsed
    cout << "Time elapsed: " << elapsed << endl;

    // Multiply sum by 1/n
    sum = sum * (1.0/n);

    // Output the final output
    cout << "The clustering coefficient of the graph is: " << setprecision(5) << sum << endl;
	
	return 0;
}
