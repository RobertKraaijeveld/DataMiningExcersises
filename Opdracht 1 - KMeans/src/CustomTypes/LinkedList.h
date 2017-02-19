#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "GenericVector.h"
#include <string>


using namespace std;

struct Item {
    string key; 
    //GenericVector vector;
    Item * next;
    Item(string k, Item *n);
    Item();
};

class LinkedList 
{
    private:
        Item * head;
        int length;

    public:
        LinkedList();
        void insert(Item * item);
        Item * get(string itemKey);
        bool remove(string itemKey);
        void print();
};

#endif