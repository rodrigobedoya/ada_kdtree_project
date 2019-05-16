#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
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
	 		/* stringstream sstream2; */
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
		heap.clear();

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
			heap.clear();
			
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
			if (node->comparingVal() < cmp->comparingVal())
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

	//write tree structure in file
	void write()
	{
		//erase previous data in file
		ofstream file;
		file.open("tree.txt");
		file.close();


		vector<Node<T>*> level;
		level.push_back(root);
		int cmp = root->getIndex();
		writeLevel(level,cmp);
	}

	void writeLevel(vector<Node<T>*> level,int cmp)
	{
		ofstream file;
		file.open("tree.txt",std::ios_base::app);

		
		file << cmp << " ";
		bool flag = false;
		vector<Node<T>*> new_level;
		for(int i = 0; i < level.size();i++)
		{
			if(level[i]==NULL)
			{
				file << "N ";
				new_level.push_back(NULL);
				new_level.push_back(NULL);
			}
			else
			{
				flag = true;
				file << level[i]->comparingVal() << " ";
				new_level.push_back(level[i]->leftChild);
				new_level.push_back(level[i]->rightChild);

			}
		}
		file << endl;
		++cmp;
        if(cmp == k){cmp = 0;}
		file.close();
		if(flag)
		{
			writeLevel(new_level,cmp);
		}
	}

    bool equalNodes(Node<T> *node1,Node<T> *node2) {
        for (int i = 0; i < k; ++i) {
            if (node1->pos(i) != node2->pos(i))
                return false;
        }
        return true;
    }

    bool searchR(Node<T> *root, Node<T> *node, unsigned coordinates) {
        if (root == NULL)
            return false;
        if (equalNodes(root,node))
            return true;
        unsigned axis = coordinates % k;

        if (node->pos(axis) < root->pos(axis))
            return searchR(root->leftChild, node, coordinates + 1);

        return searchR(root->rightChild, node, coordinates + 1);
        
    }

    bool search(Node<T> *node) {
        return searchR(root, node, 0);
    }

    void buscarVecinoskk(Node<T> *nodo) {
        if (!search(nodo))
            return;

        map<double, Node<T>*> distancias;
        for (int i = 0; i < nodes.size(); ++i) {
            distancias.insert(pair<double, Node<T>*> (nodo->ecuclidiana(nodes[i]), nodes[i]));
        }
int i= 0;
        for(auto it = distancias.begin(); it != distancias.end(); ++it) {
        if (i != 0) {
        cout << it->first << " " << it->second << endl;
        }
        if(i==3)
            break;
        i++;
    }
    
    }
};

#endif
