#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include "../machine/machine.cpp"
#include <iostream>
#include <fstream>

class MachineController {
public:
    MachineController() {};
    MachineController(const std::string&);
    
    void initializeStates();
    void initializeTransitions();
    void initalizeMachine(const std::string&, State*);
    void initTwoMachines(Machine& first, Machine& second);
    void initLoopMachines(Machine& whileMachine, Machine& main);
    void initZeroMachine(Machine& zeroMachine);
    void initXMachine(Machine& XMachine);
    void initDecider(Machine& decider);
    void initMultiMachine(Machine& main, std::vector<Machine> machines);

    void readStates(std::vector<std::string>& states, std::string location);
    void readTransitions(std::vector<Transition>& transitions, std::string location);
    void readSingleTape(std::string& tape, std::string location);
    void readMultiTape(std::vector<std::string>& tapes, std::string location);

    void runMachine();
private:
    Machine machine;
    std::string combineMachineTapes(std::vector<Machine>);
    State* getState(const std::string&);
};

#endif