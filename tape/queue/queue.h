#ifndef __QUEUE_H
#define __QUEUE_H

#include <iostream>
#include <cassert>
#include <list>

template <typename T>
class Queue {
public:
    void enqueue(const T& x); // add at end
    void dequeue(); // remove at start
    void print() const; 
private:
    struct Node {
        T data;
        Node* next;
    };

    Node *first, *last;
};

#endif