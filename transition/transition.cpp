#ifndef TRANSITION_CPP
#define TRANSITION_CPP

#include "transition.h"

Transition::Transition(char read, char write, char cmd, State* state) {
    this->read = read;
    this->write = write;
    this->cmd = cmd;    
    this->state = state;
}

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

