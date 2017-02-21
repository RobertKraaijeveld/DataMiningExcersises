#include "KMeans.h"
#include "../CustomTypes/Point.h"
#include "../CustomTypes/GenericVector.h"
#include <iostream>
#include <limits>

using namespace std;


vector<Centroid> KMeans::createRandomCentroids()
{
    //todo: make this dynamic?
    const int ROW_COUNT = 32;
    vector<Centroid> returnVector;

    for(int i = 0; i < clusterAmount; i++)
    {
        GenericVector randomGv = GenericVector::getRandomVector(ROW_COUNT);
        returnVector.push_back(Centroid(i, randomGv));
    }
    return returnVector;
}

void KMeans::reassignPointClusters()
{
    //for every poin
}

Centroid KMeans::getClosestCentroid(Point p)
{
    pair<Centroid, double> closestCentroidAndDistance (Centroid closestCentroid, numeric_limits<double>::max());

    for(int i = 0; i < centroids.size(); i++)
    {
        double distance = p.vector.getEuclidDistance(centroids[i].vector); 
        if(distance < closestCentroidAndDistance.get(1))
        {
            closestCentroidAndDistance = pair<Centroid, double> (centroids[i], distance);
        }
    }
    return closestCentroidAndDistance.get(0);
}


//use changedBool instead of previous/next
void KMeans::run(int iterationAmount)
{
    centroids = createRandomCentroids(); 

    int iterations = 0;

    //use SSE later, for now just use K
    while(iterations < iterationAmount)
    {
        //reassignPointClusters();
        //recomputeCentroids();
        std::cout << "ran" << "\n";
        iterations++;
    }
    //PrintResult(); 
}


/*
To obtain good results, this algorithm must be executed a certain number of times (how many is specified in
the input parameters): at the end of every execution, you must compute the SSE (Sum of Squared Errors) of the
solution obtained, and keep only the best solution found until that moment (that is, the one with lowest SSE).

OUTPUT
At the end of the execution, you have to print the best solution found (that is, the clustering associated to the
smallest SSE). Together with the result of clustering, print also the value of the associated SSE. Compare your
solution with that of the book to see if they match2
You can try first to execute your program with 4 clusters
(𝑘 = 4) and then with 5 (𝑘 = 5): the book shows the results in both cases.
*/