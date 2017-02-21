#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser/CsvParser.h"

using namespace std;

int main()    
{
	/*
	//0: var& = adress of non-pointer
	//1: type * var = new pointer
	//2: type *var = deref pointer, so get actual value at this pointer 
	*/

	string line;
	ifstream ifs;
	ifs.open("E:\\Hogeschool\\Data Science (Jaar 3)\\Opdracht 1 - KMeans\\docs\\wine.csv");

	//no constructor parentheses necessary for 0 arg constructor
	CsvParser parser;
	vector<GenericVector> result = parser.read(ifs);

	for(int i = 0; i < result.size(); i++)
	{
		cout << result[i].ToString() << endl;
	}




	cin.get(); 
	return 0;
}