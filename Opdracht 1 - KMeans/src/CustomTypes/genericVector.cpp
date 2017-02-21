#include "GenericVector.h"
#include <math.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;



GenericVector::GenericVector(vector<int> v)
{
    values = v;
}

double GenericVector::getEuclidDistance(GenericVector gv)
{
    if (!this->VectorSizesEqual(gv))
        return -1.0;

    double sumOfSquaredSubtractions;
    for (vector<int>::size_type i = 0; i != values.size(); i++)
    {
        sumOfSquaredSubtractions = sumOfSquaredSubtractions + pow(values[i] - gv.values[i], 2);
    }
    return sqrt(sumOfSquaredSubtractions);
}

bool GenericVector::VectorSizesEqual(GenericVector v)
{
    return v.values.size() == values.size();
}

string GenericVector::ToString()
{
    string returnStr = "(";

    for (vector<int>::size_type i = 0; i != values.size(); i++)
    {
        stringstream stream;
        stream << (values[i]);
        string strResult = stream.str();
        const char *consChar = strResult.c_str();

        if (i == (values.size() - 1))
        {
            returnStr = returnStr + *consChar + ")";
        }
        else
        {
            returnStr = returnStr + *consChar + ",";
        }
    }
    return returnStr;
}
