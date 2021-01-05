#ifndef __OPERATIONS_CPP
#define __OPERATIONS_CPP

#include "operations.h"

void Operations::composition() {
    // Machine m1,m2;
}
void Operations::decider() {
    Machine decider("001101");
    State* init = new State("init");
    State* reject = new State("reject");
    State* halt = new State("halt");

    Transition* q01 = new Transition('0', '0', 'L', reject);
    Transition* q10 = new Transition('1', '1', 'L' ,halt);

    decider.addState(reject);
    decider.addState(halt);

    decider.setCurrentState(init);

    Machine first("001101"),second("001101");
    if (decider.finishedSuccessfuly()) {
        first.start();
    } else {
        second.start();
    }

    // decider has 2 transitions check if 1->1{halt}, if 0->0{reject}

    // if (decider)
    //     first with the same input 
    // else 
    //     second with the same input

    MachineController first("001101");  // transitions -> transform everything in 1
    MachineController second("001101"); // transitions -> transofrm everything in 0
}

void Operations::loopOverMachine() {

}


void Operations::initTwoMachines(Machine*& first, Machine*& second) {
    // first - writes zeros
    // second - writes ones
    
    State* q0 = new State("q0");
    State* q1 = new State("q1");

    first->addState(q0);
    second->addState(q1);
    
    Transition* q00 = new Transition('0', '0', 'L', q0);
    Transition* q10 = new Transition('1', '0', 'L', q0);
    Transition* q01 = new Transition('0', '1', 'L', q1);
    Transition* q11 = new Transition('1', '1', 'L', q1);

    first->findState("q0")->addTransition(q00);
    first->findState("q0")->addTransition(q10);
    second->findState("q1")->addTransition(q01);
    second->findState("q1")->addTransition(q11);
}

#endif