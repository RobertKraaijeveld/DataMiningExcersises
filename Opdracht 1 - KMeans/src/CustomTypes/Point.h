#ifndef POINT_H
#define POINT_H

#include "GenericVector.h"

struct Centroid {
    int clusterId; 
    bool positionChanged;
    GenericVector vector;
    Centroid(int id, GenericVector vector);
    Centroid(){ clusterId = -1; vector = GenericVector(); };
};


class Point {
    public:
        Point(int cId, GenericVector vector);
        int centroidId;
        GenericVector vector;
};

#endif