#ifndef TRANSITION_CPP
#define TRANSITION_CPP

#include "transition.h"

Transition::Transition(char _read, char _write, char _cmd, State* _state) :
    read(_read), write(_write), cmd(_cmd), state(_state) {}

Transition::Transition(Transition other, State* other_state) {
    this->read = other.getReadSymbol();
    this->write = other.getWriteSymbol();
    this->cmd = other.getCommand();
    this->state = other_state;
}

Transition& Transition::operator=(const Transition& other) {
    this->state = other.state;
    this->read = other.read;
    this->write = other.write;
    this->cmd = other.cmd;
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

void Transition::print() const {
    std::cout << read << '/' << write << "{" << state->getName() << "}" << cmd << std::endl;
}

std::ostream& operator<<(std::ostream& out, Transition& transition) {
    /* out << transition.getReadSymbol() << '/' << transition.getWriteSymbol() << "," 
    << transition.getCommand() << std::endl; */

    State* s = transition.getNextState();
    out << transition.getWriteSymbol() << '{' << s->getName() << "}";
    return out;
}


#endif

