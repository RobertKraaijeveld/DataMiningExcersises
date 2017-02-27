#include <string>
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "CsvParser.h"
#include "../CustomTypes/GenericVector.h"
#include "../CustomTypes/Point.h"

using namespace std;


char strToChar(string s)
{
    char returnChar;
    for(int i = 0; i < s.length(); i++)
    {
        returnChar += s[i];
    }
    return returnChar;
}

vector<Point> CsvParser::parseToPoints(ifstream& fileStr)
{
    vector<Point> finalResult;
    string line;
    int rowCounter;

    while( getline(fileStr, line) )
    {
        rowCounter++;
        vector<float> valuesForVector;
        
        stringstream linestr (line);
        string cell;

        while(getline(linestr, cell, ','))
        {
            float vectorFactor = (float) atoi(cell.c_str());;
            valuesForVector.push_back(vectorFactor);
        }
        GenericVector newVector (valuesForVector);
        Point newPoint (rowCounter, newVector);

        finalResult.push_back(newPoint);
    }
    return finalResult;  
}

