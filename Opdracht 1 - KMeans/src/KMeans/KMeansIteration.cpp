#include "KMeansIteration.h"
#include "../CustomTypes/Point.h"
#include "../CustomTypes/GenericVector.h"
#include <iostream>
#include <limits>
#include <math.h>


using namespace std;


vector<Centroid> KMeansIteration::createRandomCentroids()
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

void KMeansIteration::reassignPointClusters()
{
    for(int i = 0; i < points.size(); i++)
    {
        pair<Centroid, double> closestCentroidAndDistance = getClosestCentroidAndDistance(points[i]);  
        points[i].centroidId = closestCentroidAndDistance.first.id;
        points[i].distanceToCentroid = closestCentroidAndDistance.second;
    }
}

//ERROR: Not all centroids are checked
pair<Centroid, double> KMeansIteration::getClosestCentroidAndDistance(Point p)
{
    //duplicated in kmeanscontroller
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
    return closestCentroidAndDistance;
}


void KMeansIteration::recomputeCentroids()
{
    //sum all points within a cluster, divide the resulting vector by the amount of points.
    
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
    }
}

vector<Point> KMeansIteration::getPointsOfCluster(int centroidId)
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


double KMeansIteration::computeSSE()
{
    double SSE;
    for(int i = 0; i < points.size(); i++)
    {
        SSE = SSE + pow(points[i].distanceToCentroid, 2);
    }
    return SSE;
}

void KMeansIteration::runIteration()
{
    centroids = createRandomCentroids(); 
    reassignPointClusters();    
    recomputeCentroids();

    sumOfSquaredErrors = computeSSE();
}