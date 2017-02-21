#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser/CsvParser.h"
#include "CustomTypes/Point.h"
#include "KMeans/KMeans.h"

using namespace std;


void setStreamCsvLocation(ifstream& ifs)
{
	cout << "Enter the full directory to your wine.csv file: ";
	string location;
	getline (cin, location);

	ifs.open(location);

	if(ifs.fail())
	{
		cout << "This file does not exist." << endl;
		setStreamCsvLocation(ifs);
	}
}

int main()    
{
	/*
	//0: var& = adress of non-pointer
	//1: type * var = new pointer
	//2: type *var = deref pointer, so get actual value at this pointer 
	*/
	
	ifstream ifs;
	setStreamCsvLocation(ifs);

	// /home/robert/Documents/Projects/dataminingexcersises/Opdracht 1 - KMeans/docs/wine.csv

	CsvParser parser;
	vector<Point> parsedPoints = parser.parseToPoints(ifs);

	int amountOfClusters = 15;
	int amountOfIterations = 5;

	KMeans kmeans (amountOfClusters, parsedPoints);
	kmeans.run(amountOfIterations);

	cin.get(); 
	return 0;
}
