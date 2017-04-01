#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../CustomTypes/GenericVector.h"
#include "../CustomTypes/Point.h"

using namespace std;

class CsvParser
{
    public:
     vector<Point> parseToPoints(ifstream& str);
};

#endif