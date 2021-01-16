#ifndef MACHINE_CPP
#define MACHINE_CPP

#include "machine.h"
#include <fstream>

Machine::Machine(const std::string& input, State* start = nullptr) : tape(Tape(input)), currentState(start) {
    fileName = "machine.txt";
    out.open(fileName.c_str(), std::ofstream::app);
}

Machine::Machine() {}

Machine::Machine(const Machine& other) {
    this->copy(other);
}

Machine& Machine::operator=(const Machine& other) {
    if (this != &other) {
        this->copy(other);
    }

    return *this;
}

void Machine::addState(State* state) {
    states.push_back(state);
}

State* Machine::findState(const std::string& stateName) {
    for(State* s : states) {
        if (s->getName() == stateName) {
            return s; 
        }
    }
    return nullptr;
}

bool Machine::isThereState(const std::string& stateName) {
    for(State* s : states) {
        if (s->getName() == stateName)
            return true;
    }

    return false;
}

void Machine::setCurrentState(State* currentState) {
    this->currentState = currentState;
}

void Machine::setTape(const std::string& input) {
    tape = Tape(input);
}

std::string Machine::getTape() const {
    return tape.getTapeString();
}

void Machine::print() const {
    tape.printWithCurr();
}

void Machine::iterate() {
    out << tape.read() << *currentState << " -> ";

    Transition* next = currentState->getTransition(tape.read());
    
    if (next == nullptr) {
        out << "{error}\nThe machine could not finish!" << std::endl;
        currentState = nullptr;
        return;
    }
    
    out << *next << next->getCommand() << std::endl;

    tape.write(next->getWriteSymbol());
    
    char cmd = next->getCommand();
    switch (cmd) {
        case 'L':
            tape.moveLeft();
            break;
        case 'R':
            tape.moveRight();
            break;
        case 'H':
            tape.moveNot();
            break;
        default:
            break;
    };

    currentState = next->getNextState();
}

void Machine::start() {
    while (currentState != nullptr && currentState->getName() != "halt") {
        iterate();
    }   
        
    if (finishedSuccessfuly()) {
        out << "Machine finished successfuly!\n" << std::endl;
    }
}

bool Machine::finishedSuccessfuly() const {
    return currentState != nullptr && currentState->getName() == "halt";
}

void Machine::copy(const Machine& other) {
    states = other.states;
    currentState = other.currentState;
    tape = other.tape;
    fileName = other.fileName;
}


#endif