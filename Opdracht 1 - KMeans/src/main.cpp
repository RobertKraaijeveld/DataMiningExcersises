#include <iostream>
#include<vector>
#include "CustomTypes/genericVector.h"

using namespace std;

int main()  
{
	vector<int> y;
	y.push_back(100);
	y.push_back(10);
	genericVector v1 (y);

	vector<int> z;
	z.push_back(1);
	z.push_back(50);
	genericVector v2 (z);

	cout << "distance between v1 and v2 = " << v1.getEuclidDistance(v2) << endl;
	cin.get(); // get one more char from the user

	return 0;
}