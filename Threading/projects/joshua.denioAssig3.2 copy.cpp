/*
Author: Joshua DeNio
Date:   04/01/2020

Program: Assignment02
Description: 

To compile: g++ -O3 -w joshua.denioAssig3.cpp -lpthread -o joshua.denioAssig3
To run: ./joshua.denioAssig3 filename n

example:
./joshua.denioAssig3 toyGraph1.txt 4
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

AdjacencyMatrix adjMatrix;
AdjacencyMatrix adjList;

int n;
double sum1 = 0.0;
double sum2 = 0.0;

// Counter for approach 2
long long counter = 0;

pthread_mutex_t sum_lock;
pthread_mutex_t counter_lock;

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

// Function name: thread_work1
// Input: void* rank
// Output: none
// Precondition: Must have valid data
// Postcondition: Threads work on their sections (even and odd).
void* thread_work1(void* rank);

// Function name: thread_work2
// Input: void* rank
// Output: none
// Precondition: Must have valid data
// Postcondition: Threads work on their sections (one at a time) and update sum.
void* thread_work2(void* rank);

// End of function declairations ***************

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

void* thread_work1(void* rank)
{
    // cast the rank to a long
    long my_rank = (long) rank;
    long long i;

    // Number of connections locally
	double local_sum = 0.0;


    //------------
    for (i = my_rank ; i < n; i=i+thread_count)
    {
        printf("Thread Rank: %ld Working on : %lld\n", my_rank, i);
        
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

    //-----------

    // Lock mutex, increment count and unlock
   pthread_mutex_lock(&sum_lock);
   sum1 += local_sum;
   pthread_mutex_unlock(&sum_lock);

}

void* thread_work2(void* rank)
{
    // cast the rank to a long
    long my_rank = (long) rank;

    long long i;

	double local_sum = 0.0;

    //------------
    //while(TRUE) get the work done
    while(1){ 

        pthread_mutex_lock(&counter_lock);
        i = counter;
        counter++;
        pthread_mutex_unlock(&counter_lock);

        if(i>=n) break;

        printf("Thread Rank: %ld Working on : %lld\n", my_rank, i);
      
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
    //------------

    // Lock mutex, increment count and unlock
   pthread_mutex_lock(&sum_lock);
   sum2 += local_sum;
   pthread_mutex_unlock(&sum_lock);

}

int main(int argc, char** argv)
{
	if(argc<2){
      cout<<"To run: ./joshua.denioAssig3 filename"<<endl;
      cout<<"./joshua.denioAssig3 toyGraph1.txt"<<endl;
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


    //*** Start approach 1 ***

    // Line to set up start
    GET_TIME(start);

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread], NULL, thread_work1, (void*)thread);
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
    cout << "Time elapsed using approach 1: " << elapsed << endl;

    // Multiply sum by 1/n
    sum1 = sum1 * (1.0/n);

    // Output the final output
    cout << "The clustering coefficient of the graph using approach 1 is: " << setprecision(5) << sum1 << endl;

    // *** End approach 1 ***

    // *** Start approach 2 ***
    // Line to set up start
    cout << "Starting approach 2" << endl;
    GET_TIME(start);

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread], NULL, thread_work2, (void*)thread);
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
    cout << "Time elapsed using approach 2: " << elapsed << endl;

    // Multiply sum by 1/n
    sum2 = sum2 * (1.0/n);

    // Output the final output
    cout << "The clustering coefficient of the graph using approach 2 is: " << setprecision(5) << sum2 << endl;
    // *** End approach 2 ***
	
	return 0;
}
