#include "genericVector.h"
#include <math.h>  
#include <vector>

using namespace std;

genericVector::genericVector(vector<int> v)
{
    values = v;
}

double genericVector::getEuclidDistance(genericVector gv)
{
    double sumOfSquaredSubtractions;
    for(vector<int>::size_type i = 0; i != values.size(); i++)
    {
        sumOfSquaredSubtractions = sumOfSquaredSubtractions + pow(values[i] - gv.values[i], 2);
    }
    return sqrt(sumOfSquaredSubtractions);
}

bool genericVector::VectorSizesEqual(genericVector v)
{
    return v.values.size() == values.size();
}

