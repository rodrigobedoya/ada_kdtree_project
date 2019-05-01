#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "clnode.h"
#include "cliterator.h"
#include <stdexcept>

using namespace std;

template <typename T>
class ClList {
    private:
        ClNode<T>* start;
        int nodes;

    public:
        ClList()
        {
            start = NULL;
            nodes = 0;
        }

        T front()
        {
            if(start==NULL)
                throw out_of_range("empty list");
            return start->data;
        }

        T back()
        {
            return start->prev->data;
        }

        void push_front(T value)
        {
            if (start == NULL)
            {
                start = new ClNode<T>;
                start->data = value;
                start->next = start;
                start->prev = start;
                nodes++;
                return;
            }

            ClNode<T> *temp = new ClNode<T>;
            temp->data = value;
            temp->next = start;
            temp->prev = start->prev;
            start->prev->next = temp;
            start->prev = temp;
            start = temp;
            nodes++;
            return;
        }

        void push_back(T value)
        {
            if (start == NULL)
            {
                start = new ClNode<T>;
                start->data = value;
                start->next = start;
                start->prev = start;
                nodes++;
                return;
            }

            ClNode<T> *temp = new ClNode<T>;
            temp->data = value;
            temp->next = start;
            temp->prev = start->prev;
            start->prev->next = temp;
            start->prev = temp;
            nodes++;
            return;
        }


        void pop_front()
        {
            if(start == NULL)
                return;

            ClNode<T> *temp = start;
            nodes--;
            if(start->next == start)
            {
                start = NULL;
                temp->killSelf();
                return;
            }
            
            start->prev->next = start->next;
            start = start->next;
            start->prev = temp->prev;
            temp->killSelf();
            return;

        }

        void pop_back()
        {
            if(start == NULL)
                return;
            
            ClNode<T> *temp = start->prev;

            if(nodes == 1)
            {
                start = NULL;
                temp->killSelf();
                return;
            }

            temp->prev->next = start;
            start->prev = temp->prev;
            temp->killSelf();
            nodes--;
            return;   
        }
        
        T get(int position)
        {   
            if(nodes == 0)
            {
                throw out_of_range("Empty List!");
            }   

            if (position >= nodes || position < 0)
            {
                throw out_of_range("Request is out of range!");
            }

            ClNode<T> *temp = start;
            for (int i = 0; i < nodes; i++)
            {
                if(i == position)
                {
                    return temp->data;
                }
                temp = temp->next;   
            }
        }


        T operator [] (int position)
        {
            if(nodes == 0)
            {
                throw out_of_range("Empty List!");
            }   

            if (position >= nodes || position < 0)
            {
                throw out_of_range("Request is out of range!");
            }

            ClNode<T> *temp = start;
            for (int i = 0; i < nodes; i++)
            {
                if(i == position)
                {
                    return temp->data;
                }
                temp = temp->next;   
            }
        }


        void concat(ClList<T> &other)
        {
            nodes += other.nodes;

            if(other.start == NULL )
            {
                return;
            }

            else if(start == NULL)
            {
                start = other.start;
                return;
            }


            ClNode<T> *tail1 = start->prev;
            ClNode<T> *tail2 = other.start->prev;

            tail1->next = other.start;
            start->prev = tail2;
            tail2->next = start;
            other.start->prev = tail1;
        }
        
        bool empty()
        {
            return start == NULL;
        }

        int size()
        {
            return nodes;

            /* //if nodes attr wasn't there
            int length = 0;
            if(start == NULL)
                return length;

            Node<T> *temp = start;
            
            do
            {
                length++;
                temp = temp->next
            }
            while(temp != start);

            return length;*/
        }
        
        void clear()
        {
            if(start == NULL)
                return;

            ClNode<T> *temp = start->next;
            while(temp != start)
            {
                ClNode<T> *to_delete = temp;
                temp = temp->next;
                to_delete->killSelf();
            }
            start = NULL;
            temp->killSelf();
            nodes = 0;
            return;
        }

        ClIterator<T> begin()
        {
            ClIterator<T> begin(start);
            return begin;
        }

        ClIterator<T> end()
        {
            ClIterator<T> end(start->prev);
            return end;
        }

        ~ClList(){}
};

#endif