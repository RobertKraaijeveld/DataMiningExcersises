#include "LinkedList.h"
#include "GenericVector.h"
#include <string>
#include <iostream>

using namespace std;

Item::Item(string k, Item *n)
{
    key = k;
    //vector = NULL;
    next = n;
}

Item::Item()
{
    key = "";
    //vector = NULL;
    next = NULL;
}

LinkedList::LinkedList()
{
    head = new Item();
    length = 0;
}

void LinkedList::insert(Item * newItem)
{
    if (!head->next)
    {
        head->next = newItem;
        length++;
        return;
    }

    Item * first = head;
    Item * second = head;

    while (second)
    {
        //move up
        first = second;
        second = first->next;
    }
    first->next = newItem;
    newItem->next = NULL;
    length++;
}

Item *LinkedList::get(string itemKey)
{
    Item *comparer = head;
    Item *traveller = head;

    while (traveller)
    {
        //P is the comparer, q the traveller
        comparer = traveller;

        //head is always set empty by the constr and p is set to be q, so it cant be what we are looking for.
        if ((comparer != head) && comparer->key == itemKey)
            return comparer;

        //if we did not find the item, we move on a link.
        traveller = comparer->next;
    }
    return NULL;
}

bool LinkedList::remove(string itemKey)
{
    Item *traveller = head;
    Item *comparer = head;

    while (comparer)
    {
        if (comparer->key == itemKey)
        {
            //comparer is not the node at travellers position's next anymore,
            //since it will be deleted, we set it to be the next of next instead.
            traveller->next = comparer->next;
            delete comparer;
            length--;

            return true;
        }
        //Comparer moves forward ahead of traveller
        traveller = comparer;
        comparer = traveller->next;
    }
    return false;
}

void LinkedList::print()
{
    if (length == 0)
    {
        cout << "Empty linkedlist";
        return;
    }

    Item *comparer = head;
    Item *traveller = head;

    cout << "\n{";
    while (traveller)
    {
        //move comparer one step further (except on first iteration)
        comparer = traveller;

        //we never print head since its not user set value
        if (comparer != head)
        {
            if (comparer->next != NULL)
                cout << comparer->key << ","; 
            else
                cout << comparer->key;
        }
        traveller = comparer->next;
    }
    cout << "}\n";
}
