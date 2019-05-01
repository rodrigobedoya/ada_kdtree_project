#include <iostream>
#include "kdtree.h"

using namespace std;


int main()
{
	KdTree<int> tree;
	tree.load("data.txt");
	

	// testing heaps

	int arr[11] = {10,9,8,18,7,6,5,4,3,2,1};
	
	MinHeap<int> heap(11);
	MaxHeap<int> heap2(11);
	MedianHeap<int> heap3(11);
	MedianHeap<int> heap5(11);
	MedianHeap<int> heap6(11);

	for(int i = 0; i < 11; i++)
	{
		heap.insert(arr[i]);
		heap2.insert(arr[i]);
		heap3.insert(arr[i]);
	}

	heap5.build(heap);
	heap6.build(heap2);

	cout << heap.getMin()<<endl;
	cout << heap2.getMax()<<endl;
	cout << heap3.getMedian()<<endl;
	cout << heap5.getMedian()<<endl;
	cout << heap6.getMedian()<<endl;



	//testing heap with node*	
	MinHeap<Node<int>*> heap4(5);
	
	Node<int>* prt = new Node<int>({0,1});
	Node<int>* prt2 = new Node<int>({2,3});

	heap4.insert(prt);heap4.insert(prt2);
	cout << *(heap4[0]->comparingVal)<<endl;
	heap4[0]->nextComparingVal();
	cout << *(heap4[0]->comparingVal)<<endl;


	return 0;
}