#include <string>
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "CsvParser.h"
#include "../CustomTypes/GenericVector.h"

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

//TODO: Change this to column instead of row
vector<GenericVector> CsvParser::read(ifstream& fileStr)
{
    vector<GenericVector> finalResult;
    string line;

    while( getline(fileStr, line) )
    {
        stringstream linestr (line);
        string cell;
        vector<int> valuesForVector;


        while(getline(linestr, cell, ','))
        {
            int vectorFactor = atoi(cell.c_str());;
            valuesForVector.push_back(vectorFactor);
            //cout << "cell = " << cell << endl;
        }
        GenericVector newVector (valuesForVector);
        finalResult.push_back(newVector);
    }

    /*
    while(getline(fileStr, line));
    {
        cout << "line" << endl;
        stringstream currentLine(line);
        string cell;

        vector<int> valsForVector;

        while (getline(currentLine, cell, ','))
        {
            cout << "cell" << endl;
            int vectorFactor = (int) strToChar(cell);
            valsForVector.push_back(vectorFactor);
        }
        GenericVector vectorForThisLine(valsForVector);
        finalResult.push_back(vectorForThisLine);
    }
     */
    return finalResult;
}

