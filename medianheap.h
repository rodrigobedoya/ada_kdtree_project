#ifndef MEDH_H
#define MEDH_H
#include "minheap.h"
#include "maxheap.h"

template <typename T>
class MedianHeap 
{ 
	int size;
	MinHeap<T> * right;
	MaxHeap<T> * left;
public:
	MedianHeap(int size)
	{
		this->size = size;
		right = new MinHeap<T>(size/2 +2);
		left = new MaxHeap<T>(size/2 +2);
	}    

	void build(Heap<T> heap)
	{
		for(int i = 0; i < heap.getSize();i++)
		{
			insert(heap[i]);
		}
		return;	
	}

	void insert(T value)
	{
		if(value < left->getMax() || left->getSize() == 0)
			left->insert(value);
		
		else
			right->insert(value);

		if(left->getSize() - right->getSize() > 1)
		{
			int key = left->extractMax();
			right->insert(key);
		}
		else if (right->getSize() - left->getSize() > 1)
		{
			int key = right->extractMin();
			left->insert(key);
		}
	}

	T getMedian()
	{
		return left->getMax();
	}
}; 



#endif