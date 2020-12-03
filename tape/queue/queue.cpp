#ifndef __QUEUE_CPP
#define __QUEUE_CPP

#include "queue.h"

template <typename T>
void Queue<T>::enqueue(const T& x) {
    Node* temp = new Node{x,nullptr};

    if (first == nullptr) {
        first = last = temp;
        return;
    }

    last->next = temp;
    last = temp;
}

template <typename T>
void Queue<T>::dequeue() {
    if (first == nullptr)
        return;

    Node* temp = first;
    first = first->next;

    if (first == nullptr)
        last = nullptr;

    delete temp;
}

template <typename T>
void Queue<T>::print() const {
    Node* curr = first;

    while (curr!=nullptr) {
        std::cout << curr->data << " ";
        curr=curr->next;
    }

    std::cout << std::endl;
}

#endif