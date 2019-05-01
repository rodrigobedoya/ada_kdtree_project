#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "node.h"
#include "medianheap.h"


using namespace std;

template <typename T>
class KdTree
{
public:
	int k;
	Node<T>* root;
	vector<Node<T>*> nodes;
	KdTree()
	{
		root = NULL;
	}

	KdTree(string filename)
	{
		root = NULL;
		load(filename);
	}

	void add(vector<T> position)
	{
		Node<T> * temp = new Node<T>(position);
		if(nodes.size() == 0)
		{
			root = temp;
		}
		nodes.push_back(temp);
	}

	void load(string fileName)
	{
		ifstream file;
		file.open(fileName);

		string line;
		getline(file, line);
		
		stringstream sstream;
		int size;
		
		sstream << line;
		sstream >> size >> k;
		nodes.reserve(size);

		
		for(int i = 0; i < size;i++) 
	 	{
	 		vector<T> pos(k,0);
	 		getline(file, line);
	 		stringstream sstream2;
	 		sstream.clear();
	 		sstream << line;
	 		
	 		for(int j = 0; j < k; j++)
	 		{
	 			sstream >> pos[j];
	 		}

	 		Node<T> * temp = new Node<T>(pos);
	 		nodes.push_back(temp);
		}

		for(int i = 0; i < nodes.size();i++)
		{
			insert(nodes[i],root);	
		}
				
	}

	void insert(Node<T>* node, Node<T>* cmp)
	{
		if(cmp == NULL)
		{
			if(root == NULL)
				root = node;
			else
				cmp = node;
		}

		else
		{
			if (*(node->comparingVal) < *(cmp->comparingVal))
			{
				node->nextComparingVal();
				if(cmp->leftChild == NULL)
				{
					cmp->leftChild = node;
				}
				else
					insert(node, cmp->leftChild);
			}
			else
			{
				node->nextComparingVal();
				if(cmp->rightChild == NULL)
					cmp->rightChild = node;
				else
					insert(node,cmp->rightChild);
			}
		}
	}

};

#endif