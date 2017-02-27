#ifndef GENERICVECTOR_H
#define GENERICVECTOR_H

#include <string>
#include <vector>

using namespace std;


class GenericVector
{ 
   public:
    vector<float> values;   

    //bad robert, using hardcoded column values like that
    GenericVector(){ values = vector<float>(32, 0.0);  };
    GenericVector(vector<float> v);

    float getEuclidDistance(GenericVector& gv);
    GenericVector sumWith(GenericVector& gv);
    GenericVector divide(int divisor);

    static GenericVector getRandomVector(int dimensionLength);
    bool VectorSizesEqual(GenericVector& gv);
    string ToString();
};

#endif