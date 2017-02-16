#ifndef GENERICVECTOR_H
#define GENERICVECTOR_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class CsvParser
{
    private:
     
     istream& fileStr;
     void readNextRow();

    public: 
      int* getResult(istream& file);
};

#endif