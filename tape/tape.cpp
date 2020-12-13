#ifndef TAPE_CPP
#define TAPE_CPP

#include "tape.h"

Tape::Tape() {
    for (size_t i = 0; i < 10; i++) {
        list.push_back(SPACE);
    }

    curr = list.getLast();
}

Tape::Tape(const std::string& input) {
    int size = input.size();
    for(int i = 0; i < size; i++) {
        list.push_back(input[i]);
    }

    curr = list.getLast();
    currIndex = size - 1;
    list.push_back(SPACE);
}

Tape::Tape(const DLL<char> list) {
    this->list = list;
}

void Tape::print() const {
    int size = list.size();
    for(int i = 0; i < size; i++) {
        std::cout << list[i] << " | ";
    }

    std::cout << std::endl;
}

void Tape::printWithCurr() const {
    int size = list.size();
    for(int i = 0; i < size; i++) {
        std::cout << list[i] << " | ";
    }

    std::cout << std::endl;

    for (int i = 0; i < currIndex; i++) {
        std::cout << "    ";
    }

    std::cout << "/" << std::endl;
}

const char Tape::operator[](size_t i) {
    return list[i];
}

void Tape::write(char c) {
    curr = c;
    list[currIndex] = c;
}

char Tape::read() const {
    return curr;
}

int Tape::readIndex() const {
    return currIndex;
}

void Tape::moveRight() {
    if (list.getLast() == '\0')
        list.push_back(SPACE);

    curr = list[++currIndex];
}

void Tape::moveLeft() {
    if (list.getFirst() == '\0')
        list.push(SPACE);

    curr = list[--currIndex];
}

void Tape::moveNot() {
    // не правим нищо
}

#endif
