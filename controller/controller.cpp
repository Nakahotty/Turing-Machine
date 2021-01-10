#ifndef __CONTROLLER_CPP
#define __CONTROLLER_CPP

#include "controller.h"

MachineController::MachineController(const std::string& input) : machine(Machine(input)) {}

void MachineController::initializeStates() {
    // ----- Инициализираме състоянията и преходите ----- //

    State* q0 = new State("q0");
    State* q1 = new State("q1");
    State* q2 = new State("q2");
    State* halt = new State("halt");

    machine.addState(q0);
    machine.addState(q1);
    machine.addState(q2);
    machine.addState(halt);

    machine.setCurrentState(q0);
}   

void MachineController::initializeTransitions() {
    // ----- Добавяме състоянията в машината както и преходите между тях ----- //
    Transition* q01 = new Transition('0', '1', 'L', getState("q1"));
    Transition* q02 = new Transition('1', '0', 'R', getState("q2"));
    Transition* q11 = new Transition('0', '0', 'L', getState("q1"));
    Transition* q12 = new Transition('1', '0', 'R', getState("q2"));
    Transition* q21 = new Transition('0', '1', 'H', getState("q2"));
    Transition* q22 = new Transition('1', '1', 'L', getState("halt"));

    machine.findState("q0")->addTransition(q01);
    machine.findState("q0")->addTransition(q02);
    machine.findState("q1")->addTransition(q11);
    machine.findState("q1")->addTransition(q12);
    machine.findState("q2")->addTransition(q21);
    machine.findState("q2")->addTransition(q22);
}

void MachineController::initalizeMachine(const std::string& tape, State* initState) {
    machine = Machine(tape,initState);
}

void MachineController::runMachine() {
    initializeStates();
    initializeTransitions();

    machine.print();
    machine.start();
    machine.print();
    std::cout << "Finished: " << machine.finishedSuccessfuly() << std::endl;
}

State* MachineController::getState(const std::string& s) {
    return machine.findState(s);
}

void MachineController::initTwoMachines(Machine& first, Machine& second) {
    // first - writes ones
    // second - writes zeros
    State* init = new State("init");
    State* q0 = new State("q0");
    State* q1 = new State("q1");
    State* halt = new State("halt");

    first.addState(init);
    first.addState(q1);
    first.setCurrentState(init);
    
    Transition* q01 = new Transition('0', '1', 'L', q1);
    Transition* q11 = new Transition('1', '1', 'L', q1);
    Transition* q_ = new Transition(' ', ' ', 'R', halt);
    
    first.findState("init")->addTransition(q01);
    first.findState("init")->addTransition(q11);
    first.findState("q1")->addTransition(q01);
    first.findState("q1")->addTransition(q11);
    first.findState("q1")->addTransition(q_);

    initZeroMachine(second);
}

void MachineController::initZeroMachine(Machine& zeroMachine) {
    State* toZero = new State("to zero"); 
    State* init = new State("init");
    State* halt = new State("halt");

    Transition* q00 = new Transition('0', '0', 'L', toZero);
    Transition* q10 = new Transition('1', '0', 'L', toZero);
    Transition* q_ = new Transition(' ', ' ', 'R', halt);

    zeroMachine.addState(init);
    zeroMachine.addState(halt);
    zeroMachine.addState(toZero);

    zeroMachine.setCurrentState(init);
    zeroMachine.findState("init")->addTransition(q10);
    zeroMachine.findState("init")->addTransition(q00);
    zeroMachine.findState("to zero")->addTransition(q00);
    zeroMachine.findState("to zero")->addTransition(q10);
    zeroMachine.findState("to zero")->addTransition(q_);
}

void MachineController::initXMachine(Machine& XMachine) {
    State* toX = new State("X"); 
    State* init = new State("init");
    State* halt = new State("halt");

    Transition* q0X = new Transition('0', 'X', 'L', toX);
    Transition* q1X = new Transition('1', 'X', 'L', toX);
    Transition* q_ = new Transition(' ', ' ', 'R', halt);

    XMachine.addState(init);
    XMachine.addState(halt);
    XMachine.addState(toX);

    XMachine.setCurrentState(init);
    XMachine.findState("init")->addTransition(q1X);
    XMachine.findState("init")->addTransition(q0X);
    XMachine.findState("X")->addTransition(q0X);
    XMachine.findState("X")->addTransition(q1X);
    XMachine.findState("X")->addTransition(q_);
}

#endif