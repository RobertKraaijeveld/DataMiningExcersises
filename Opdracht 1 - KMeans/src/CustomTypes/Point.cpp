#include "Point.h"
#include "GenericVector.h"

Point::Point(int cId, GenericVector gv)
{
    centroidId = cId;
    vector = gv;
}

//note to self: Centroid objs dont have to be remade, only their previousGv/currentGvs's
Centroid::Centroid(int i, GenericVector gv)
{
    id = i;
    vector = gv;
}

int Centroid::getOfferCount(int offerId)
{
    for()
}



