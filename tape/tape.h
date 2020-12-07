#ifndef __TAPE_H
#define __TAPE_H

#include <iostream>
#include "queue/queue.h"
#include "list/dll.h"

template <typename T>
class Tape {
public:
    Tape();
    Tape(const DLL<T> list);
    void print() const;
    const T& operator[](size_t i);
private:
    DLL<T> list;
};

#endif