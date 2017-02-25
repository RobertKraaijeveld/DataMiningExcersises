#ifndef KMEANSCONTROLLER_H
#define KMEANSCONTROLLER_H

#include "../CustomTypes/Point.h"
#include "../CustomTypes/GenericVector.h"
#include "KMeansIteration.h"

class KMeansController {
    private:
        int iterationAmount;
        int clusterAmount;

        vector<Point>& points;
        vector<KMeansIteration> iterations;

        KMeansIteration getIterationWithBestSSE();
        void printResult(KMeansIteration& iteration);

    public:
        KMeansController(vector<Point> &p, int k, int c) : points(p)  { iterationAmount = k; clusterAmount = c; };
        void run();
                
};


#endif