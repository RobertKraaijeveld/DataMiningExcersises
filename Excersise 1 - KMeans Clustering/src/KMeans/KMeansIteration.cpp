#include "KMeansIteration.h"
#include "../CustomTypes/Point.h"
#include "../CustomTypes/GenericVector.h"
#include <iostream>
#include <limits>
#include <math.h>
#include <map>

using namespace std;

//shitty param, get rid of it
bool KMeansIteration::centroidsHaveChanged()
{
    for(int i = 0; i < clusterAmount; i++)
    {
        if(centroids[i].hasChanged)
            return true;   
    }    
    return false;
}

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
        pair<Centroid, float> closestCentroidAndDistance = getClosestCentroidAndDistance(points[i]);  
        points[i].centroidId = closestCentroidAndDistance.first.id;
        points[i].distanceToCentroid = closestCentroidAndDistance.second;
    }
}

pair<Centroid, float> KMeansIteration::getClosestCentroidAndDistance(Point p)
{
    //duplicated in kmeanscontroller
    float MAX_float = 1.7976931348623158e+308;
    Centroid closestCentroid;
    pair<Centroid, float> closestCentroidAndDistance = make_pair(closestCentroid, MAX_float);

    for(int i = 0; i < centroids.size(); i++)
    {
        float distance = p.vector.getEuclidDistance(centroids[i].vector); 

        if(distance < closestCentroidAndDistance.second)
            closestCentroidAndDistance = make_pair(centroids[i], distance);                        
            
    }
    return closestCentroidAndDistance;
}


void KMeansIteration::recomputeCentroids()
{
    //sum all points within a cluster, divide the resulting vector by the amount of points.
    for(int i = 0; i < centroids.size(); i++)
    {
        GenericVector oldVector = centroids[i].vector;
        vector<Point> pointsForThisCluster = KMeansIteration::getPointsOfCluster(centroids[i].id);

        for(int j = 0; j < pointsForThisCluster.size(); j++)
        {
            GenericVector& vectorForPoint = pointsForThisCluster[j].vector;
            centroids[i].vector.sumWith(vectorForPoint);            
        }
        centroids[i].vector.divide(pointsForThisCluster.size());      

        recordVectorChange(oldVector, centroids[i]);
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

void KMeansIteration::recordVectorChange(GenericVector& oldCentroidVector, Centroid& centroid)
{
    centroid.hasChanged = oldCentroidVector.isNotEqual(centroid.vector);
}  



/*
REPORTING RESULTS
*/

map<int, int> KMeansIteration::getCentroidOfferCounts(Centroid& centroid)
{
    vector<Point> pointsForCluster = getPointsOfCluster(centroid.id);

    map<int, int> offerCountsForCentroid;

    for (int j = 0; j < pointsForCluster.size(); j++)
    {
        for(int i = 0; i < pointsForCluster[j].vector.values.size(); i++)
        {
            if(pointsForCluster[j].vector.values[i] == 1.0)
            {
                offerCountsForCentroid[i] = offerCountsForCentroid[i] + 1;
            }
        }
    }
    return offerCountsForCentroid;
}

void KMeansIteration::printCentroidOffersAboveThreshold(int threshold, Centroid& centroid)
{
    map<int,int> offersCounts = getCentroidOfferCounts(centroid);
    int offersAboveThresholdCount = 0;

    cout << "ITERATION " << iterationId << " - CENTROID NO. " << centroid.id << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Total amount of offers bought: " << offersCounts.size() << endl;
    cout << "---------------------------------------------------" << endl;
    

    //sort this
    for (int k = 0; k < offersCounts.size(); k++)
    {
        if(offersCounts.count(k) && offersCounts[k] > threshold)
        {
            offersAboveThresholdCount++;
            cout << "Offer " << k << " was bought " << offersCounts[k] << " times" << endl;            
        }
    }

    if(offersAboveThresholdCount == 0 && offersCounts.size() > 0)
    {
        cout << "No offers in this cluster were bought more than " << threshold << " times." << endl;
    }
    cout << "" << endl;
    cout << "" << endl;
}

void KMeansIteration::print(int offerThreshold)
{
    for(int i = 0; i < centroids.size(); i++)
    {
        printCentroidOffersAboveThreshold(offerThreshold, centroids[i]);
    }
}

float KMeansIteration::computeSSE()
{
    float SSE = 0;
    for(int i = 0; i < points.size(); i++)
    {
        SSE += powf(points[i].distanceToCentroid, 2.0);
    }
    return SSE;
}


void KMeansIteration::runIteration()
{
    centroids = createRandomCentroids(); 
    
    int count = 0;
    while(count < 25)
    {
        reassignPointClusters();    
        recomputeCentroids();
        count++;

        if(centroidsHaveChanged() == false)
            break;
    }
    sumOfSquaredErrors = computeSSE();
}

/*
check the distance between the original centroid vector and its new one. Should get smaller and smaller
as it homes in.
*/
