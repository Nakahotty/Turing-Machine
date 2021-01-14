#ifndef __CONTROLLER_CPP
#define __CONTROLLER_CPP

#include "controller.h"
#include <fstream>
#include <iostream>

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

void MachineController::initLoopMachines(Machine& whileMachine, Machine& main) {
    std::vector<std::string> read_states;
    this->readStates(read_states);

    State* init = new State(read_states[0]);
    State* halt = new State(read_states[1]);
    State* searchOne = new State(read_states[2]);

///////////////////////////////////////////////////

    std::vector<Transition*> transitions;
    this->readTransitions(transitions);
    
    Transition* q00 = new Transition('0', '0', 'L', searchOne);
    Transition* q11 = new Transition('1', '1', 'H', halt);

//////////////////////////////////////////

    whileMachine.addState(init);
    whileMachine.addState(searchOne);
    whileMachine.addState(halt);

    whileMachine.setCurrentState(init);
    whileMachine.findState("init")->addTransition(q00);
    whileMachine.findState("init")->addTransition(q11);
    whileMachine.findState("searchOne")->addTransition(q00);
    whileMachine.findState("searchOne")->addTransition(q11);

    State* addChar = new State(read_states[3]);
    
    Transition* writeChar = new Transition('0', '5', 'L', addChar);
    Transition* startChar = new Transition('9', 'X', 'L', addChar);
    Transition* writeOnSpace = new Transition(' ', '5', 'L', addChar);

    main.addState(init);
    main.addState(addChar);
    main.addState(halt);

    main.setCurrentState(init);
    main.findState("init")->addTransition(startChar);
    main.findState("addChar")->addTransition(writeChar);
    main.findState("addChar")->addTransition(writeOnSpace);
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

void MachineController::initDecider(Machine& decider) {
    State* init = new State("init");
    State* reject = new State("reject");
    State* halt = new State("halt");

    Transition* rejection = new Transition('0', '0', 'L', reject); // няма да завърши 
    Transition* success = new Transition('1', '1', 'L' ,halt);

    decider.addState(init);
    decider.addState(reject);
    decider.addState(halt);

    decider.setCurrentState(init);
    decider.findState("init")->addTransition(rejection);
    decider.findState("init")->addTransition(success);
}


void MachineController::readStates(std::vector<std::string>& states) {
    std::fstream state_file("./txt/loop/states.txt");
    std::string state; 
    while (std::getline(state_file,state)) {
        states.push_back(state);
    }
    state_file.close();
}

void MachineController::readTransitions(std::vector<Transition*>& transitions) {
    std::fstream trans_file("./txt/loop/transitions.txt");
    char read,write,cmd;
    std::string trans_line;

    while(std::getline(trans_file, trans_line)) {
        if (trans_line == "-WHILE")
            continue;

        if (trans_line == "-MAIN")
            continue;

        int startIndex = 4;

        read = trans_line[0];
        write = trans_line[2];
        
        std::string stateString;

        while (trans_line[startIndex] != '}') {
            stateString+=trans_line[startIndex];
            ++startIndex;
        }

        ++startIndex;
        cmd = trans_line[startIndex];
    
        State* to_state = new State(stateString);
        Transition* trans = new Transition(read,write,cmd,to_state);
        transitions.push_back(trans);
    }

    trans_file.close();

    for (int i = 0; i < transitions.size(); i++) {
        transitions[i]->print();
        std::cout << transitions[i]->getNextState()->getName() << std::endl;
    }
}

#endif