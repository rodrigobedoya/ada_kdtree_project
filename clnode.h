#ifndef CLNODE_H
#define CLNODE_H

#include <iostream>

using namespace std;

template <typename T>
struct ClNode {
    T data;
    ClNode* next;
    ClNode* prev;

    void killSelf()
    {
    	delete this;
    }
    
};

#endif
