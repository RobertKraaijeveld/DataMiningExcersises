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

    pair<int&, float> bestIterationIdAndSSE (iterations[0].iterationId, iterations[0].sumOfSquaredErrors);

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
            cout << "" << endl;            
            cout << "============================" << endl;
            cout << "BEST ITERATION has id " << bestIterationIdAndSSE.first << " and SSE " << bestIterationIdAndSSE.second << endl; 
            cout << "============================" << endl;
            cout << "" << endl;
            
            return iterations[j];            
        }
    }
}


//TODO: set iterationAmount by user
void KMeansController::run()
{
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
    bestIteration.print(3.0);
    cout << "DONE" << endl;
}

