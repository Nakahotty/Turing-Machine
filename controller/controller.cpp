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

/////////////////////////////////////////////////////////////////////////

void MachineController::initTwoMachines(Machine& first, Machine& second) {
    // first - writes ones
    // second - writes zeros

    std::vector<std::string> read_states;
    std::string state_file = "./txt/decider/states.txt";
    this->readStates(read_states, state_file);

    State* init = new State(read_states[0]);
    State* halt = new State(read_states[1]);
    State* q0 = new State(read_states[3]);
    State* q1 = new State(read_states[4]);

    first.addState(init);
    first.addState(q1);
    first.setCurrentState(init);

    std::vector<Transition> transitions;
    std::string trans_file = "./txt/decider/transitions.txt";
    this->readTransitions(transitions, trans_file);
    
    Transition* q01 = new Transition(transitions[2], q1);
    Transition* q11 = new Transition(transitions[3], q1);
    Transition* q_ = new Transition(transitions[4], halt);
    
    first.findState("init")->addTransition(q01);
    first.findState("init")->addTransition(q11);
    first.findState("q1")->addTransition(q01);
    first.findState("q1")->addTransition(q11);
    first.findState("q1")->addTransition(q_);

    initZeroMachine(second);
}

void MachineController::initLoopMachines(Machine& whileMachine, Machine& main) {
    std::vector<std::string> read_states;
    std::string state_file = "./txt/loop/states.txt";
    this->readStates(read_states, state_file);

    State* init = new State(read_states[0]);
    State* halt = new State(read_states[1]);
    State* searchOne = new State(read_states[2]);

    std::vector<Transition> transitions;
    std::string trans_file = "./txt/loop/transitions.txt";
    this->readTransitions(transitions, trans_file);
    
    Transition* q00 = new Transition(transitions[0], searchOne);
    Transition* q11 = new Transition(transitions[1], halt);

    whileMachine.addState(init);
    whileMachine.addState(searchOne);
    whileMachine.addState(halt);

    whileMachine.setCurrentState(init);
    whileMachine.findState("init")->addTransition(q00);
    whileMachine.findState("init")->addTransition(q11);
    whileMachine.findState("searchOne")->addTransition(q00);
    whileMachine.findState("searchOne")->addTransition(q11);

    State* addChar = new State(read_states[3]);
    
    Transition* writeChar = new Transition(transitions[2], addChar);
    Transition* startChar = new Transition(transitions[3], addChar);
    Transition* writeOnSpace = new Transition(transitions[4], addChar);

    main.addState(init);
    main.addState(addChar);
    main.addState(halt);

    main.setCurrentState(init);
    main.findState("init")->addTransition(startChar);
    main.findState("addChar")->addTransition(writeChar);
    main.findState("addChar")->addTransition(writeOnSpace);
}

void MachineController::initZeroMachine(Machine& zeroMachine) {    
    std::vector<std::string> states;
    std::string state_file = "./txt/composition/states.txt";
    readStates(states, state_file);

    State* init = new State(states[0]);
    State* halt = new State(states[1]);
    State* toZero = new State(states[2]); 

    std::vector<Transition> transitions;
    std::string trans_file = "./txt/composition/transitions.txt";
    readTransitions(transitions,trans_file);

    Transition* q00 = new Transition(transitions[0], toZero);
    Transition* q10 = new Transition(transitions[1], toZero);
    Transition* q_ = new Transition(transitions[2], halt);

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
    std::vector<std::string> states;
    std::string state_file = "./txt/composition/states.txt";
    readStates(states, state_file);

    State* init = new State(states[0]);
    State* halt = new State(states[1]);
    State* toX = new State(states[3]);
    
    std::vector<Transition> transitions;
    std::string trans_file = "./txt/composition/transitions.txt";
    readTransitions(transitions, trans_file);

    Transition* q0X = new Transition(transitions[3], toX);
    Transition* q1X = new Transition(transitions[4], toX);
    Transition* q_ = new Transition(transitions[5], halt);

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
    std::vector<std::string> states;
    std::string state_file = "./txt/decider/states.txt";
    readStates(states, state_file);

    State* init = new State(states[0]);
    State* halt = new State(states[1]);
    State* reject = new State(states[2]);

    std::vector<Transition> transitions;
    std::string trans_file = "./txt/decider/transitions.txt";
    readTransitions(transitions, trans_file);

    Transition* rejection = new Transition(transitions[0], reject); // няма да завърши 
    Transition* success = new Transition(transitions[1],halt);

    decider.addState(init);
    decider.addState(reject);
    decider.addState(halt);

    decider.setCurrentState(init);
    decider.findState("init")->addTransition(rejection);
    decider.findState("init")->addTransition(success);
}

void MachineController::initMultiMachine(Machine& main, std::vector<Machine> machines) {
    std::vector<std::string> states_strings;
    std::string state_file = "./txt/multi/states.txt";
    readStates(states_strings, state_file);

    State* init = new State(states_strings[0]);
    State* halt = new State(states_strings[1]);
    State* toNine = new State(states_strings[2]);
    State* toLilX = new State(states_strings[3]);
    State* toExclamation = new State(states_strings[4]);
    State* separated = new State(states_strings[5]);

    std::vector<Transition> transitions;
    std::string trans_file = "./txt/multi/transitions.txt";
    readTransitions(transitions, trans_file);

    Transition* q09 = new Transition(transitions[0], toNine);
    Transition* q11 = new Transition(transitions[1], toNine);
    Transition* q__ = new Transition(transitions[4], halt);

    Transition* qXx = new Transition(transitions[2], toLilX);
    Transition* q1ex = new Transition(transitions[3], toExclamation);
    Transition* qStar = new Transition(transitions[5], separated);

    main.addState(init);
    main.addState(halt);

    main.setCurrentState(init);
    main.findState("init")->addTransition(q09);
    main.findState("init")->addTransition(q11);
    main.findState("init")->addTransition(qStar);

    std::string mutli_tape;
    size_t size = machines.size();
    for(size_t i = 0; i < size; i++) {
        mutli_tape+= '*' + machines[i].getTape();
    } 

    std::vector<State*> newStates;
    newStates.push_back(toNine);
    newStates.push_back(toLilX);
    newStates.push_back(toExclamation);
    newStates.push_back(separated);

    main.addState(toNine);
    main.addState(toLilX);
    main.addState(toExclamation);
    main.addState(separated);

    main.addToTape(mutli_tape);

    for (size_t i = 0; i < newStates.size(); i++) {
        std::string stateName = newStates[i]->getName();
        main.findState(stateName)->addTransition(q09);
        main.findState(stateName)->addTransition(q1ex);
        main.findState(stateName)->addTransition(qXx);
        main.findState(stateName)->addTransition(qStar);
        main.findState(stateName)->addTransition(q__);
    }
    
    main.start();
    main.print();
}

void MachineController::readStates(std::vector<std::string>& states, std::string location) {
    std::fstream state_file(location);
    std::string state; 
    while (std::getline(state_file,state)) {
        states.push_back(state);
    }
    state_file.close();
}

void MachineController::readTransitions(std::vector<Transition>& transitions, std::string location) {
    std::fstream trans_file(location);
    std::string trans_line;

    while(std::getline(trans_file, trans_line)) {
        char read,write,cmd;

        if (trans_line[0] == '-')
            continue;

        int startIndex = 4;

        if (trans_line[0] == '_')
            read = ' ';
        else 
            read = trans_line[0];

        if (trans_line[2] == '_')
            write = ' ';
        else 
            write = trans_line[2];

        std::string stateString;
        while (trans_line[startIndex] != '}') {
            stateString+=trans_line[startIndex];
            ++startIndex;
        }

        ++startIndex;
        cmd = trans_line[startIndex];
    
        State* to_state = new State(stateString);
        Transition trans(read,write,cmd,to_state);
        transitions.push_back(trans);
    }

    trans_file.close();
}

void MachineController::readSingleTape(std::string& tape, std::string location) {
    std::fstream read_tape(location);
    std::getline(read_tape,tape);
}

void MachineController::readMultiTape(std::vector<std::string>& tapes, std::string location) {
    std::fstream read_tape(location);
    std::string tape;
    
    while (std::getline(read_tape,tape)) {
        tapes.push_back(tape);
    }
}

#endif