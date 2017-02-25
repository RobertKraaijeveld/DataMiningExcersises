#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser/CsvParser.h"
#include "CustomTypes/Point.h"
#include "KMeans/KMeansController.h"

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

/*
pair<int, int> getIterationAndClusterAmount(ifstream& ifs)
{
	cout << "Enter the full directory to your wine.csv file: ";
	string location;
	getline (cin, location);
	
		if(ifs.fail())
	{
		cout << "This file does not exist." << endl;
		setStreamCsvLocation(ifs);
	}
}
*/

int main()    
{
	ifstream ifs;
	setStreamCsvLocation(ifs);

	// /home/robert/Documents/Projects/dataminingexcersises/Opdracht 1 - KMeans/docs/wine.csv

	CsvParser parser;
	vector<Point> parsedPoints = parser.parseToPoints(ifs);

	int amountOfClusters = 5;
	int amountOfIterations = 4;

	KMeansController kmeansController(parsedPoints, amountOfIterations, amountOfClusters);
	kmeansController.run();

	cin.get(); 
	return 0;
}
