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

	//read data from file and add it to vector: nodes
	void load(string fileName)
	{
		nodes.clear();
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
	}

	void print()
	{
		// Format: { <level> : <position>}
		printRecursive(root);
		cout << endl;
	}

	void printRecursive(Node<T>* node)
	{
		if(node->leftChild != NULL)
		{
			printRecursive(node->leftChild);
		}
		node->print();
		if(node->rightChild != NULL)
		{
			printRecursive(node->rightChild);
		}
		
	}


	// create balanced tree(need loadedd data)
	void build()
	{
		MedianHeap<Node<T>*> heap(nodes.size());
		for(int i = 0; i < nodes.size();i++)
		{
			heap.insert(nodes[i]);
		}
		root = heap.getMedian();
		heap.extractMedian();

		MedianHeap<Node<T>*> left(heap.left);
		MedianHeap<Node<T>*> right(heap.right);
		
		buildRecursive(left,root->leftChild);
		buildRecursive(right,root->rightChild);
	}


	void buildRecursive(MedianHeap<Node<T>*> heap,Node<T>*& cmp)
	{
		if (heap.getSize() == 0)
		{
			cmp = NULL;
		}

		else
		{
			cmp = heap.getMedian();
			heap.extractMedian();

			MedianHeap<Node<T>*> left(heap.left);
			MedianHeap<Node<T>*> right(heap.right);
			
			buildRecursive(left,cmp->leftChild);
			buildRecursive(right,cmp->rightChild);
		}
	}


	//insert elements without balancing tree
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