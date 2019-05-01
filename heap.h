#ifndef HEAP_H
#define HEAP_H

template <typename T>
class Heap
{
public:
	T *data;  
	int max_size;
	int size;

public:
    
	Heap(){}
    ~Heap(){}

    int getSize()
    {
    	return size;
    }

    T operator [] (int index)
    {
    	return Heap<T>::data[index];
    }

    T getRoot() 
    {
    	return Heap<T>::data[0];
    }

    virtual T extractRoot(){}
    virtual int insert() {}
    virtual void decreaseKey() {}
    virtual void heapify() {}

protected:
	void swap(T *x, T *y) 
	{ 
	    T temp = *x; 
	    *x = *y; 
	  
	  *y = temp; 
	}



	int parentIndex(int i)
	{ 
		return (i-1)/2; 
	}

    int leftIndex(int i) 
    {
    	return (2*i + 1);
    } 

    int rightIndex(int i) 
    { 
    	return (2*i + 2); 
    } 


};

#endif