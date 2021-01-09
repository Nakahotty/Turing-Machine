#ifndef __OPERATIONS_CPP
#define __OPERATIONS_CPP

#include "operations.h"

void Operations::composition() {
    // Дадено: 2 машини - Т1, Т2; вход - А
    // А = 11011 | Т1(А) -> 00000 | T2(T1(A)) -> XXXXX
    // Композиция: done
}
void Operations::decider() {
    Machine decider("001101");
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
    decider.start();
    decider.print();

    Machine first("001101"),second("001101");
    initTwoMachines(first, second);
    if (decider.finishedSuccessfuly()) {
        std::cout << "Decider finished SUCCESSFULY!" << std::endl;
        first.start();
        std::cout << first.finishedSuccessfuly() << std:: endl;
        first.print();
    } else {
        std::cout << "Decider did NOT FINISH!" << std::endl;
        second.start();
        std::cout << second.finishedSuccessfuly() << std:: endl;
        second.print();
    }
}

void Operations::loopOverMachine() {

}


void Operations::initTwoMachines(Machine& first, Machine& second) {
    // first - writes zeros
    // second - writes ones
    
    State* init = new State("init");
    State* q0 = new State("q0");
    State* q1 = new State("q1");
    State* halt = new State("halt");

    first.addState(init);
    first.addState(q0);
    second.addState(init);
    second.addState(q1);

    first.setCurrentState(init);
    second.setCurrentState(init);
    
    Transition* q00 = new Transition('0', '0', 'L', q0);
    Transition* q10 = new Transition('1', '0', 'L', q0);
    Transition* q01 = new Transition('0', '1', 'L', q1);
    Transition* q11 = new Transition('1', '1', 'L', q1);
    Transition* q_ = new Transition(' ', ' ', 'R', halt);

    first.findState("init")->addTransition(q00);
    first.findState("init")->addTransition(q10);
    first.findState("q0")->addTransition(q00);
    first.findState("q0")->addTransition(q10);
    first.findState("q0")->addTransition(q_);
    
    second.findState("init")->addTransition(q01);
    second.findState("init")->addTransition(q11);
    second.findState("q1")->addTransition(q01);
    second.findState("q1")->addTransition(q11);
    second.findState("q1")->addTransition(q_);
}

#endif