#ifndef MAXH_H
#define MAXH_H
#include <climits>
#include "heap.h"


template <typename T>
class MaxHeap : public Heap<T>
{ 

public: 
	MaxHeap(int max_size) 
	{ 
	    Heap<T>::size = 0; 
	    Heap<T>::max_size = max_size; 
	    Heap<T>::data = new T[max_size]; 
	}
    
    int getMax() 
    { 
    	return Heap<T>::data[0];
    } 
  	
  	int insert(T k) 
	{ 
	    if (Heap<T>::size == Heap<T>::max_size) 
	    { 
	        return -1; 
	    } 
	  
	    Heap<T>::size++; 
	    int i = Heap<T>::size - 1; 
	    Heap<T>::data[i] = k; 
	  
	    while (i != 0 && Heap<T>::data[Heap<T>::parentIndex(i)] < Heap<T>::data[i]) 
	    { 
	       Heap<T>::swap(&Heap<T>::data[i], &Heap<T>::data[Heap<T>::parentIndex(i)]); 
	       i = Heap<T>::parentIndex(i); 
	    }
	    return 0; 
	} 
	  
	void decreaseKey(int i, T new_val) 
	{ 
	    Heap<T>::data[i] = new_val; 
	    while (i != 0 && Heap<T>::data[Heap<T>::parentIndex(i)] < Heap<T>::data[i]) 
	    { 
	       Heap<T>::swap(&Heap<T>::data[i], &Heap<T>::data[Heap<T>::parentIndex(i)]); 
	       i = Heap<T>::parentIndex(i); 
	    } 
	} 
  
	T extractMax() 
	{ 
	    if (Heap<T>::size <= 0) 
	        return INT_MAX; 
	    if (Heap<T>::size == 1) 
	    { 
	        Heap<T>::size--; 
	        return Heap<T>::data[0]; 
	    } 
	  
	    T root = Heap<T>::data[0]; 
	    Heap<T>::data[0] = Heap<T>::data[Heap<T>::size-1]; 
	    Heap<T>::size--; 
	    heapify(0); 
	  
	    return root; 
	} 

	T extractRoot()
    {
    	extractMax();
    }

  
	void deleteKey(int i) 
	{ 
	    decreaseKey(i, INT_MIN); 
	    extractMax(); 
	} 
	void heapify(int i) 
	{ 
	    int l = Heap<T>::leftIndex(i); 
	    int r = Heap<T>::rightIndex(i); 
	    int biggest = i; 
	    if (l < Heap<T>::size && Heap<T>::data[l] > Heap<T>::data[i]) 
	        biggest = l; 
	    if (r < Heap<T>::size && Heap<T>::data[r] > Heap<T>::data[biggest]) 
	        biggest = r; 
	    if (biggest != i) 
	    { 
	        Heap<T>::swap(&Heap<T>::data[i], &Heap<T>::data[biggest]); 
	        heapify(biggest); 
	    } 
	} 

}; 

#endif