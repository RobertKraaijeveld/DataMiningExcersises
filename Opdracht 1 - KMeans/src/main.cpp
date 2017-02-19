#include <iostream>
#include<vector>
#include <string>
#include "CustomTypes/GenericVector.h"
#include "CustomTypes/LinkedList.h"

using namespace std;

int main()  
{
	/*
	//1: type * var = new pointer
	//2: type *var = deref pointer, so get actual value at this pointer
	*/

	vector<int> vals (3, 2);
	GenericVector vector (vals);
	string vectorAsStr = vector.ToString();
	cout << vectorAsStr << endl;

	LinkedList * list = new LinkedList[13]; 
	Item * newItem1 = new Item("key1", NULL);
	Item * newItem2 = new Item("key2", NULL);

	list->insert(newItem1);
	list->insert(newItem2);

	cout << "Looking for key key2: " << list->get(newItem2->key)->key << endl;
	list->print();

	//TODO: Write destructors to delete dynam mem
	//add value to linked item
	//create hashtable stuff
	//write simple csv to hashtable<GenericVector> 
	//do kmeans with said hashtable
	//display pretty result

	cin.get(); 
	return 0;
}