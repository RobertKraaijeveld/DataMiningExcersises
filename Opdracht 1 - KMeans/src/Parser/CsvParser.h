#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../CustomTypes/GenericVector.h"

using namespace std;

class CsvParser
{
    public:
     vector<GenericVector> read(ifstream& str);
};

#endif