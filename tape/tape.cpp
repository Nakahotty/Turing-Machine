#ifndef __TAPE_CPP
#define __TAPE_CPP

#include "tape.h"

Tape::Tape() {
    for (size_t i = 0; i < 10; i++) {
        list.push_back(' ');
    }
}

Tape::Tape(const DLL<char> list) {
    this->list = list;
}

void Tape::print() const {
    list.print();
}

const char& Tape::operator[](size_t i) const {

}

#endif
