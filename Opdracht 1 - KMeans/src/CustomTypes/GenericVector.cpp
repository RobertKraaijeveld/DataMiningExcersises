#include "GenericVector.h"
#include <math.h>
#include <random>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

GenericVector::GenericVector(vector<int> v)
{
    values = v;
}

double GenericVector::getEuclidDistance(GenericVector other)
{
    if (!this->VectorSizesEqual(other))
        return -1.0;

    double sumOfSquaredSubtractions;
    for (vector<int>::size_type i = 0; i != values.size(); i++)
    {
        sumOfSquaredSubtractions = sumOfSquaredSubtractions + pow(values[i] - other.values[i], 2);
    }
    return sqrt(sumOfSquaredSubtractions);
}

GenericVector GenericVector::sum(GenericVector other)
{
    if (!this->VectorSizesEqual(other))
        return GenericVector(vector<int>(1,-1));

    vector<int> summedValues;
    for(int i = 0; i < values.size(); i++)
    {
        summedValues[i] = (values[i] + other.values[i]);
    }
    return GenericVector(summedValues);
}

GenericVector GenericVector::getRandomVector(int dimensionLength)
{
    random_device rd;
 
    //Mersenne Twister pseudo-random number generator
    mt19937 gen(rd());
 
    //distributor in range
    uniform_int_distribution<> distributor(0, 1);
 
    vector<int> values;
    for (int i = 0; i < dimensionLength; i++)
    {
        values.push_back(distributor(gen));
    }
    return GenericVector(values);
}


bool GenericVector::VectorSizesEqual(GenericVector other)
{
    return other.values.size() == values.size();
}

string GenericVector::ToString()
{
    string returnStr = "(";

    for (int i = 0; i != values.size(); i++)
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
