#ifndef KMEANS_H
#define KMEANS_H

#include "../CustomTypes/Point.h"
#include "../CustomTypes/GenericVector.h"

class KMeans {
    private:
        int clusterAmount;
        vector<Point> &points;
        vector<Centroid> centroids;
        
        vector<Centroid> createRandomCentroids();
        bool continueIteration();
        void reassignPointClusters();
        Centroid getClosestCentroid(Point p);

        vector<Point> getPointsOfCluster(int centroidId);
        void recomputeCentroids();
        
        void printResult();

    public:
        KMeans(int c, vector<Point>& p) : points(p) { clusterAmount = c; };
        void run(int iterationAmount);
                
};


#endif