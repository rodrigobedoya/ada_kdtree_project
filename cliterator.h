#ifndef ITERATOR_H
#define ITERATOR_H

#include "clnode.h"

template <typename T>
class ClIterator {
    private:
        ClNode<T>* current;
    
    public:
        ClIterator()
        {
            current = NULL;
        }

        ClIterator(ClNode<T>* node)
        {
            current = node;
        }
         
        ClIterator<T> operator=(ClIterator<T> node)
        {
            current = node.current;
            return *this;
        }

        bool operator!=(ClIterator<T> cmp)
        {
            return current != cmp.current;
        }

        ClIterator<T> operator++()
        {
            current = current->next;
            return *this;
        }

        ClIterator<T> operator--()
        {
            current = current->prev;
            return *this;
        }

        T operator*()
        {
            return current->data;
        }
        
};

#endif