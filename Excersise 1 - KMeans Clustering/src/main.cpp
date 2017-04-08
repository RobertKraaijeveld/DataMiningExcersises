#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser/CsvParser.h"
#include "CustomTypes/Point.h"
#include "KMeans/KMeansController.h"

using namespace std;


pair<int, int> getIterationAndClusterAmount()
{
	cout << "Enter the amount of clusters you wish to use: " << endl;
	string clusterAmountStr;
	getline (cin, clusterAmountStr);
	
	int clusterAmount = stoi(clusterAmountStr);

	cout << "Enter the amount of iterations you wish to use: " << endl;
	string algorithmIterationAmountStr;
	getline (cin, algorithmIterationAmountStr);
	
	int algorithmIterationAmount = stoi(algorithmIterationAmountStr);

	if(clusterAmount > 0 && algorithmIterationAmount > 0)
		return make_pair(algorithmIterationAmount, clusterAmount);
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

void executeKMeansRoutine(ifstream& ifs)
{
	CsvParser parser;
	vector<Point> parsedPoints = parser.parseToPoints(ifs);

	pair<int, int> amountOfIterationsAndClusters = getIterationAndClusterAmount();

	KMeansController kmeansController(parsedPoints,amountOfIterationsAndClusters.first, amountOfIterationsAndClusters.second);
	kmeansController.run();

	if(AskForRetry() == 1)
		executeKMeansRoutine(ifs);
	else
		return;
}

int main()    
{
	ifstream ifs;
	ifs.open("/home/robert/Documents/Projects/DataMiningExcersises/Excersise 1 - KMeans Clustering/docs/wine.csv");

	if(ifs.good())
	{
		executeKMeansRoutine(ifs);
	}
	else
	{
		cout << "CSV File not found. Please check if the path in main.cpp is correct." << endl;				
		cin.get();	
	}
	return 0;
}
