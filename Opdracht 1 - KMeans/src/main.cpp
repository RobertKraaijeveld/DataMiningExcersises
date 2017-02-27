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

pair<int, int> getIterationAndClusterAmount()
{
	cout << "Enter the amount of clusters you wish to use: " << endl;
	string clusterAmountStr;
	getline (cin, clusterAmountStr);
	
	int clusterAmount = stoi(clusterAmountStr);

	cout << "Enter the amount of iterations you wish to use: " << endl;
	string iterationAmountStr;
	getline (cin, iterationAmountStr);
	
	int iterationAmount = stoi(iterationAmountStr);

	if(clusterAmount > 0 && iterationAmount > 0)
	{
		return make_pair(iterationAmount, clusterAmount);
	}
	else
	{
		cout << "Please enter numbers larger than 0." << endl;
		return getIterationAndClusterAmount();
	}

}

int AskForRetry()
{
	cout << "Do you want to run the algorithm again? (Y/n)" << endl;

	string answer;
	getline (cin, answer);

	if(answer == "Y" || answer == "y")
		return 1;
	else
		return 0;
}

void executeKMeansRoutine()
{
	ifstream ifs;
	setStreamCsvLocation(ifs);

	// /home/robert/Documents/Projects/dataminingexcersises/Opdracht 1 - KMeans/docs/wine.csv

	CsvParser parser;
	vector<Point> parsedPoints = parser.parseToPoints(ifs);

	pair<int, int> amountOfIterationsAndClusters = getIterationAndClusterAmount();

	KMeansController kmeansController(parsedPoints,amountOfIterationsAndClusters.first, amountOfIterationsAndClusters.second);
	kmeansController.run();

	if(AskForRetry() == 1)
		executeKMeansRoutine();
	else
		return;

}

int main()    
{
	executeKMeansRoutine();
	return 0;
}
