#ifndef __OPERATIONS_H
#define __OPERATIONS_H

#include "../machine/machine.cpp"

class TuringOperation {
public:
    TuringOperation();
    void initializeStates();
    void initializeTransitions();
    void initalizeMachine(const std::string&, State*);

    void runMachine();
private:
    Machine machine;
    State* getState(const std::string&);
};

#endif