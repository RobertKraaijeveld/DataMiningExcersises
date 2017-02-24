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
        cout << "randomvector position = " << randomGv.ToString() << endl;
        returnVector.push_back(Centroid(i, randomGv));
    }
    return returnVector;
}


void KMeans::reassignPointClusters()
{
    for(int i = 0; i < points.size(); i++)
    {
        points[i].centroidId = getClosestCentroid(points[i]).id;
    }
}

Centroid KMeans::getClosestCentroid(Point p)
{
    double MAX_DOUBLE = 1.7976931348623158e+308;
    Centroid closestCentroid;
    pair<Centroid, double> closestCentroidAndDistance = make_pair(closestCentroid, MAX_DOUBLE);

    for(int i = 0; i < centroids.size(); i++)
    {
        double distance = p.vector.getEuclidDistance(centroids[i].vector); 

        if(distance < closestCentroidAndDistance.second)
        {
            closestCentroidAndDistance = make_pair(centroids[i], distance);                        
        }
    }
    return closestCentroidAndDistance.first;
}


void KMeans::recomputeCentroids()
{
    //sum all points within a cluster, divide the resulting vector by the amount of points.
    //4 loop, not nice

    GenericVector sumResultVector;
    for(int i = 0; i < centroids.size(); i++)
    {
        vector<Point> pointsForThisCluster = getPointsOfCluster(centroids[i].id);
        for(int j = 0; j < pointsForThisCluster.size(); j++)
        {
            GenericVector& vectorForPoint = pointsForThisCluster[j].vector;
            sumResultVector = sumResultVector.sumWith(vectorForPoint);            
        }     
        centroids[i].vector = sumResultVector.divide(pointsForThisCluster.size());
        cout << "centroid with id " << centroids[i].id << " is now at vector " << centroids[i].vector.ToString() << endl; 
    }
}

//inefficient unfortunately
vector<Point> KMeans::getPointsOfCluster(int centroidId)
{
    vector<Point> pointsForCluster;
    for(int i = 0; i < points.size(); i++)
    {
       if(points[i].centroidId == centroidId)
       {
           pointsForCluster.push_back(points[i]);
       }
    }
    return pointsForCluster;
}



//use changedBool instead of previous/next
//set iterationAmount by user
void KMeans::run(int iterationAmount)
{
    centroids = createRandomCentroids(); 

    int iterations = 0;

    //use SSE later, for now just use K
    while(iterations < iterationAmount)
    {
        reassignPointClusters();
        recomputeCentroids();
        //save result and SSE
        iterations++;
    }
    //pick result with best SSE
    //PrintResult(bestResult); 
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