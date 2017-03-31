#ifndef KMEANSITERATION_H
#define KMEANSITERATION_H

#include "../CustomTypes/Point.h"
#include "../CustomTypes/GenericVector.h"

class KMeansIteration {
    private:
        int clusterAmount;

        vector<Point> &points;
        vector<Centroid> centroids;        


        bool centroidsHaveChanged();
        vector<Centroid> createRandomCentroids();
        void reassignPointClusters();
        pair<Centroid, float> getClosestCentroidAndDistance(Point p);

        vector<Point> getPointsOfCluster(int centroidId);
        void recomputeCentroids();
        void recordVectorChange(GenericVector& oldCentroidVector, Centroid& centroid);

        float computeSSE();
        map<int, int> getCentroidOfferCounts(Centroid& centroid);
        void printCentroidOffersAboveThreshold(int threshold, Centroid& centroid);


    public:
        int iterationId;
        float sumOfSquaredErrors;

        KMeansIteration(vector<Point>& p, int& c, int& i) : points(p), clusterAmount(c),  iterationId(i){};
        void runIteration();
        void print(int offerThreshold);
};


#endif