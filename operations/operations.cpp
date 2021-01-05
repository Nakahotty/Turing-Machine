#ifndef __OPERATIONS_CPP
#define __OPERATIONS_CPP

#include "operations.h"

void Operations::composition() {
    Machine m1,m2;
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

#endif