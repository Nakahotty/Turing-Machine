#ifndef __TAPE_H
#define __TAPE_H
#pragma once

#include <iostream>
#include "queue/queue.h"
#include "list/dll.h"

class Tape {
public:
    Tape();
    Tape(const DLL<char> list);
    void print() const;
    const char& operator[](size_t i) const;

    void write(char);
    char read() const;
    void moveRight();
    void moveLeft();
private:
    DLL<char> list;
};

#endif