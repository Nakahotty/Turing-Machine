#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include "../machine/machine.cpp"

class MachineController {
public:
    MachineController(const std::string&);
    void initializeStates();
    void initializeTransitions();
    void initalizeMachine(const std::string&, State*);

    void runMachine();
private:
    Machine machine;
    State* getState(const std::string&);
};

#endif