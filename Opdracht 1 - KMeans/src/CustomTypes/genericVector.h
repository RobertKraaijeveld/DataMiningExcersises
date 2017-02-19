#ifndef GENERICVECTOR_H
#define GENERICVECTOR_H

#include <string>
#include <vector>

using namespace std;

class GenericVector
{ 
   private:  
    vector<int> values;

   public:
    GenericVector(vector<int> v);
    double getEuclidDistance(GenericVector gv);
    bool VectorSizesEqual(GenericVector v);
    string ToString();
};
//make struct for point since it only holds data, namely an id, a cluster id and this

#endif