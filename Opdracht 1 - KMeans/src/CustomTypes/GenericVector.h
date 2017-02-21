#ifndef GENERICVECTOR_H
#define GENERICVECTOR_H

#include <string>
#include <vector>

using namespace std;

class GenericVector
{ 
   public:
    vector<int> values;   

    //bad robert, using hardcoded column values like that
    GenericVector(){ values = vector<int>(32, 0);  };
    GenericVector(vector<int> v);

    double getEuclidDistance(GenericVector gv);
    GenericVector sum(GenericVector gv);
    static GenericVector getRandomVector(int dimensionLength);
    bool VectorSizesEqual(GenericVector gv);
    string ToString();
};

#endif