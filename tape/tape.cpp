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
    currIndex = size; // беше size-1, защото добавяме спейс отпред и отзад
    list.push(SPACE);
    list.push_back(SPACE);
}

Tape::Tape(const DLL<char> list) {
    this->list = list;
}


Tape& Tape::operator=(const Tape& other) {
    list = other.list;
    curr = other.curr;
    currIndex = other.currIndex;
}

void Tape::print() const {
    int size = list.size();
    for(int i = 0; i < size; i++) {
        if (i == size-1)
            std::cout << list[i];

        std::cout << list[i] << " | ";
    }

    std::cout << std::endl;
}

void Tape::printWithCurr() const {
    int size = list.size();
    for(int i = 0; i < size; i++) {
        if (i == size-1)
            std::cout << list[i];
        else  
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

std::string Tape::getTapeString() const {
    std::string res;
    int size = list.size();
    for(int i = 0; i < size; i++) {
        if (list[i] != ' ')
            res += list[i];
    }    
    return res;
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
    curr = list[++currIndex];

    if (curr == ' ')
        list.push_back(SPACE);
}

void Tape::moveLeft() {
    curr = list[--currIndex];

    if (curr == ' ') 
        list.push(SPACE);
}

void Tape::moveNot() {
    // не правим нищо
}

void Tape::addSpace() {
    list.push(SPACE);
}

#endif
