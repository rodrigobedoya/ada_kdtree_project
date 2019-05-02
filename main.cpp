#include <iostream>
#include "kdtree.h"

using namespace std;


int main()
{
	KdTree<int> tree;
	tree.load("data.txt");
	tree.build();
	tree.print();	
	return 0;
}