#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "cllist.h"
#include <vector>
using namespace std;

template <typename T>
class Node {
public:

    Node(T val)
    {
        position.push_back(val);
        comparingVal = position.begin();
    }

	Node(vector<T> args) 
	{
		for(int i = 0; i < args.size();i++)
		{
			position.push_back(args[i]);
		}
		comparingVal = position.begin();
	}
    
    ClList<T> position;
    Node* leftChild;
    Node* rightChild;
    ClIterator<T> comparingVal;

    T nextComparingVal()
    {
    	++comparingVal;
    	return *comparingVal;
    }

    bool operator < (Node<T> cmp)
    {
        return (*comparingVal < *cmp.comparingVal); 
    } 
    bool operator > (Node<T> cmp)
    {
        return (*comparingVal > *cmp.comparingVal); 
    } 

};

#endif
