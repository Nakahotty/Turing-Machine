#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include "../machine/machine.cpp"

class MachineController {
public:
    MachineController() {};
    MachineController(const std::string&);
    void initializeStates();
    void initializeTransitions();
    void initalizeMachine(const std::string&, State*);
    void initTwoMachines(Machine& first, Machine& second);
    void initZeroMachine(Machine& zeroMachine);
    void initXMachine(Machine& XMachine);

    void runMachine();
private:
    Machine machine;
    State* getState(const std::string&);
};

#endif