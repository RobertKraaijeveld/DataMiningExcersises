#ifndef KMEANSITERATION_H
#define KMEANSITERATION_H

#include "../CustomTypes/Point.h"
#include "../CustomTypes/GenericVector.h"

class KMeansIteration {
    private:
        int clusterAmount;

        vector<Point> &points;
        vector<Centroid> centroids;
        
        vector<Centroid> createRandomCentroids();
        void reassignPointClusters();
        pair<Centroid, double> getClosestCentroidAndDistance(Point p);

        vector<Point> getPointsOfCluster(int centroidId);
        void recomputeCentroids();

        double computeSSE();

    public:
        int iterationId;
        double sumOfSquaredErrors;
        
        KMeansIteration(vector<Point>& p, int& c, int& i) : points(p), clusterAmount(c),  iterationId(i) {};
        void runIteration();
};


#endif