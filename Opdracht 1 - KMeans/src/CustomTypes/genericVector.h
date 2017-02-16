#ifndef GENERICVECTOR_H
#define GENERICVECTOR_H

#include <vector>

using namespace std;

class genericVector
{ 
   private:  
    vector<int> values;

   public:
    genericVector(vector<int> v);
    double getEuclidDistance(genericVector gv);
    bool VectorSizesEqual(genericVector v);
};
//make struct for point since it only holds data, namely an id, a cluster id and this

#endif