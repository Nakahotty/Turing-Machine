#ifndef TRANSITION_CPP
#define TRANSITION_CPP

#include "transition.h"

Transition::Transition(char _read, char _write, char _cmd, State* _state) :
    read(_read), write(_write), cmd(_cmd), state(_state) {}

State* Transition::getNextState() {
    return state;
}

char Transition::getReadSymbol() const {
    return read;
}

char Transition::getWriteSymbol() const {
    return write;
}

char Transition::getCommand() const {
    return cmd;
}


#endif

