#include "KMeansController.h"
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm> 

using namespace std;

KMeansIteration KMeansController::getIterationWithBestSSE()
{
    //todo: Use sorting algorithm instead and make this a ref.
    //also, make this a null or something instead of the first
    //duplicated in kmeanscontroller

    pair<int&, double> bestIterationIdAndSSE (iterations[0].iterationId, iterations[0].sumOfSquaredErrors);

    //maybe tell iteration to calc sse here?
    for (int i = 0; i < iterations.size(); i++)
    {
        if(iterations[i].sumOfSquaredErrors <  bestIterationIdAndSSE.second)
        {
            bestIterationIdAndSSE.first = iterations[i].iterationId;
            bestIterationIdAndSSE.second =  iterations[i].sumOfSquaredErrors;
        }
    }

    for(int j =0; j < iterations.size(); j++)
    {
        if(iterations[j].iterationId == bestIterationIdAndSSE.first)
        {
            cout << "best iteration has id " << bestIterationIdAndSSE.first << " and SSE " << bestIterationIdAndSSE.second << endl; 
            return iterations[j];            
        }
    }
}

void KMeansController::printResult(KMeansIteration& iteration)
{
    for(int i = 0; i < centroids.size(); i++)
    {
        vector<Point> pointsForCluster = getPointsOfCluster(centroids[i].id);

        for (int j = 0; j < pointsForCluster.size(); j++)
        {
            
        }
    }

    /*
    for each cluster, you have to consider which clients belong to it
    and count how many times each of the 32 offers was bought by that group of clients. Then, you have to sort
    the offers in order to show only the “most bought” ones in each cluster. Display only the offers which were
    bought more than 3 times.
    */
}



//TODO: set iterationAmount by user
void KMeansController::run()
{
    cout << "RUNNING" << endl;
    int iterationsCount = 0;

    while(iterationsCount < iterationAmount)
    {
        KMeansIteration kmeansIteration(points, clusterAmount, iterationsCount);
        kmeansIteration.runIteration();

        //check if done?
        iterations.push_back(kmeansIteration);
        iterationsCount++;
    }
    KMeansIteration bestIteration = getIterationWithBestSSE();
    //printResult(bestIteration);
}

/*
Important: to improve the understandability of the results, instead of just printing which points belong to each
cluster, we need a post-processing step. The output of the algorithm should be displayed in a similar way as the
book does (see pictures 2.22, 2.23, 2.24. 2.25): for each cluster, you have to consider which clients belong to it
and count how many times each of the 32 offers was bought by that group of clients. Then, you have to sort
the offers in order to show only the “most bought” ones in each cluster. Display only the offers which were
bought more than 3 times.

Small example: suppose we have a dataset made by only 5 offers and, after executing the algorithm, one of the
clusters is composed by clients #1,#2,#3,#4,#5. Suppose also that the information we have about these clients
is the following:
Client #1 buys offers 1,2
Client #2 buys offer 3
Client #3 buys offers 2,3
Client #4 buys offer 3
Client #5 buys offers 2,3
Then, we want to print this cluster in the following way:
OFFER 3  bought 4 times (by clients of this cluster)
OFFER 2  bought 3 times
OFFER 1  bought 1 time
OFFER 4  bought 0 times
OFFER 5  bought 0 times
Clearly, the clients of this cluster prefer offers 2 and 3.
*/

