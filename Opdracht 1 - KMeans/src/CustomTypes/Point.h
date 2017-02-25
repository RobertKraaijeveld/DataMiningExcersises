#ifndef POINT_H
#define POINT_H

#include "GenericVector.h"

struct Centroid {
    int id; 
    GenericVector vector;
    Centroid(int id, GenericVector vector);
    Centroid(){ id = -1; vector = GenericVector(); };
    int getOfferCount(int offerId);
};


class Point {
    public:
        Point(int cId, GenericVector vector);
        int centroidId;
        GenericVector vector;
        double distanceToCentroid;
};

#endif
