#ifndef MACHINE_H
#define MACHINE_H

#include "../tape/tape.h"
#include "../transition/transition.h"
#include "../state/state.h"

class Machine {
public:
    Machine(const std::string&, State*);

    void addState(State*);
    State* findState(const std::string&);
    bool isThereState(const std::string&);
    
    void print();
    void iterate();
    void start();
    bool finishedSuccessfuly() const;
private:
    std::vector<State*> states; // всички състояния заданени на машината
    State* currentState; // текущото
    Tape tape;
};

#endif