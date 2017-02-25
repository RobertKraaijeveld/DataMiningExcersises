#include "GenericVector.h"
#include <math.h>
#include <random>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

GenericVector::GenericVector(vector<double> v)
{
    values = v;
}

double GenericVector::getEuclidDistance(GenericVector& other)
{
    if (!this->VectorSizesEqual(other))
    {
        //TODO MAKE THIS AN EXCEPTION
        return -1.0;        
    }

    double sumOfSquaredSubtractions;
    for (int i = 0; i < values.size(); i++)
    {
        sumOfSquaredSubtractions = sumOfSquaredSubtractions + pow(values[i] - other.values[i], 2);
    }
    return sqrt(sumOfSquaredSubtractions);
}

GenericVector GenericVector::sumWith(GenericVector &other)
{
    if (!this->VectorSizesEqual(other))
        return GenericVector(vector<double>(1,-1.0));

    vector<double> summedValues;
    for(int i = 0; i < values.size(); i++)
    {
        summedValues.push_back(values[i] + other.values[i]);
    }
    return GenericVector(summedValues);
}


GenericVector GenericVector::divide(int divisor)
{
    for (int i = 0; i < values.size(); i++)
    {
        //avoiding division by 0 errors on not-chosen clusters
        if(divisor == 0)
            divisor = 1;

        values[i] = values[i] / divisor;
    }
    return * this;
 }


GenericVector GenericVector::getRandomVector(int dimensionLength)
{
    random_device rd;
 
    //Mersenne Twister pseudo-random number generator
    mt19937 gen(rd());
 
    //distributor in range TODO: GENERIFY THIS
    uniform_int_distribution<> distributor(0, 1);
 
    vector<double> values;
    for (int i = 0; i < dimensionLength; i++)
    {
        values.push_back(distributor(gen));
    }
    return GenericVector(values);
}


bool GenericVector::VectorSizesEqual(GenericVector &other)
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

        if (i == (values.size() - 1))
        {
            returnStr = returnStr + strResult + ")";
        }
        else
        {
            returnStr = returnStr + strResult + ",";
        }
    }
    return returnStr;
}

