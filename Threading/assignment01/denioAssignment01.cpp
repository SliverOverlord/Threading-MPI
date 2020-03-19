/*
Author: Joshua DeNio
Date:   02/25/2020

Program: Assignment01
Description: This program will find and print k mutual friends of a
given node.

To compile: g++ -O3 -w denioAssignment01.cpp -lpthread -o denioAssignment01
To run: ./denioAssignment01 filename k n
example:
./denioAssignment01 toyGraph1.txt 2 4
note: k is the number of recommendations and n is the number of threads.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "timer.h"

using namespace std;


typedef vector<vector<int> > AdjacencyMatrix;

// Variable declarations
int n;
int k;
const int MAX_THREADS = 1024;
long thread_count;
// Mutex m
pthread_mutex_t lockM;

AdjacencyMatrix adjMatrix;
// Vectors
vector<pair<int,int> > allEdges;
vector<vector<int> > final_recommendations ;

//  Function declarations ****************

// Function name: thread_work
// Input: void* rank
// Output: none
// Precondition: Must have a valid vector
// Postcondition: Prints output
void* thread_work(void* rank);

// Function name: printAdjMatrix
// Input: AdjacencyMatrix
// Output: none
// Precondition: Must have a valid matrix
// Postcondition: prints matrix elements
void printAdjMatrix(AdjacencyMatrix adjMatrix);

// Function name: rev_sort
// Input: const pair<int,int> &a, const pair<int,int> &b
// Output: none
// Precondition: Must have valid input
// Postcondition: overrides sort
bool rev_sort(const pair<int,int> &a, const pair<int,int> &b);

// End function declairations ***************


int main(int argc, char** argv)
{
    if (argc < 3)
    {
        cout << "To run enter: ./denioAssignment01 filename k" << endl;
        cout << "./denioAssignment01 networkDatasets/toyGraph1.txt 2" << endl;
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

    // Variables set k from cmd line arg.
    k = atoi(argv[2]);
    int u;
    int v;
    int t;
    int maxNode = 0;

    while (myFile >> u >> v)
    {
        // Add new pair to allEdges
        allEdges.push_back(make_pair(u,v));

        if (u > maxNode)
        {
            maxNode = u;
        }
        if (v > maxNode)
        {
            maxNode = v;
        }
    }

    // Start n at +1 so we dont start at 0
    n = maxNode + 1;
    cout<<"Graph has "<< n <<" nodes"<<endl;

    // cout << "How many threads should we run?: ";
    // cin >> t;
    // cout << endl;
    // cout << t << " Threads will be used." << endl;
    // cout << endl;
    // cout << "The number of recommendations per node will be: " << k << endl;

    thread_count = atoi(argv[3]);

    adjMatrix = AdjacencyMatrix(n, vector<int>(n));
    final_recommendations = vector<vector<int> >(n);

    // Populate our matrix
    for (int i = 0; i < allEdges.size(); i++)
    {
        u = allEdges[i].first;
        v = allEdges[i].second;
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    if (n <= 10)
    {
        printAdjMatrix(adjMatrix);
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
    //printf("Time elapsed: %.15f\n",elapsed);
    cout << "Time elapsed: " << elapsed << endl;

    // print our recommendations
    for (int i = 0; i < final_recommendations.size(); i++)
    {
        cout << endl << "The recommended friends for " << i << " are: ";
        for (int j = 0; j < final_recommendations[i].size(); j++)
        {
            cout << " "<< final_recommendations[i][j];
        }
        cout << endl;
    }


}

void printAdjMatrix(AdjacencyMatrix adjMatrix)
{
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        for (int j = 0; j < adjMatrix[i].size(); j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void* thread_work(void* rank)
{
    // cast the rank to a long
    long my_rank = (long) rank;

    //Divide the work to the nodes
    int s = adjMatrix.size();

    int i;

    long long my_n = n/thread_count;

    // Start and end possitions for each thread
    long long my_start = my_n * my_rank;
    long long my_end = (my_start + my_n);

    // If the data can be evenly spread spread it or send the extra to the last thread
    if (my_rank == thread_count - 1)
    {
        my_end = (n % thread_count) + my_end ;
    }


    

    cout << "thread " << my_rank << " start " << my_start << " end " << my_end << endl;

    // For each i
    for ( i = my_start; i < my_end; i++)
    {
        // Vector to hold recomended friends
        vector< pair<int,int> > recommended_friends;

        // Check each j for common friends
        for (int j = 0; j < n; j++)
        {
            // vector containing the number of friends in common
            //vector<int> common_friends_count(n,0);
            
            if (i != j && adjMatrix[i][j] == 0)
            {
                int count = 0;
                //cout << i << ", " << j << " :: ";

                for (int k = 0; k < n; k++)
                {
                    if (adjMatrix[i][k] == 1 && adjMatrix[j][k] == 1)
                    {
                        // if k has a common friend with i but is
                        //not a freind of i ++ the counter
                        count += 1;
                    }
                }

                //common_friends_count[j] += count;
                if (count > 0)
                {
                    recommended_friends.push_back(make_pair(count, j));
                }
            }
            
        }
        if (recommended_friends.size() > 0)
        {
            vector<int> friends;

            // Sort the recommendations
            sort(recommended_friends.begin(), recommended_friends.end(), rev_sort);
            int new_k = k; 
            if (k > recommended_friends.size())
            {
                new_k = recommended_friends.size();
            }

            // send them to the main thread
            for (int j = 0; j < new_k; j++)
            {
              final_recommendations[i].push_back(recommended_friends[j].second);
            }

            
        }

    }

    return NULL;
}

bool rev_sort(const pair<int,int> &a, const pair<int,int> &b)
{ 
    return a.first > b.first; 
} 