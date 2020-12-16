#ifndef MACHINE_CPP
#define MACHINE_CPP

#include "machine.h"

Machine::Machine(const std::string& input, State* start) :
    tape(Tape(input)), currentState(start) {}

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

void Machine::print() {
    tape.printWithCurr();
}

void Machine::iterate() {
    /* 
        Получаваме прехода по подаден символ
        Записваме върху лентата символа, който е WRITE
        Проверяваме командата, за да преместим машината по лентата
        Преминаваме на следващо състояние
    */

    std::cout << tape.read() << *currentState << " -> ";

    Transition* next = currentState->getTransition(tape.read());
    
    if (next == nullptr) {
        std::cout << "{error}\nThe machine could not finish!" << std::endl;
        currentState = nullptr;
        return;
    }
    
    std::cout << *next << next->getCommand() << std::endl;

    tape.write(next->getWriteSymbol());
    
    char cmd = next->getCommand();
    switch (cmd) {
        case 'L':
            tape.moveLeft();
            break;
        case 'R':
            tape.moveRight();
            break;
        default:
            break;
    };

    currentState = next->getNextState();
}

void Machine::start() {
    while (currentState != nullptr && currentState->getName() != "halt")
        iterate();
        
    std::cout << std::endl;
}

bool Machine::finishedSuccessfuly() const {
    return currentState != nullptr && currentState->getName() == "halt";
}

#endif