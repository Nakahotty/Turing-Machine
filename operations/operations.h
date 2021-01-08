#ifndef __OPERATIONS_H
#define __OPERATIONS_H

#include "../machine/machine.h"
#include "../controller/controller.h"

class Operations {
public:
    Operations() {};
    void composition();
    void decider();
    void loopOverMachine();

    // helpers
    void initTwoMachines(Machine& first, Machine& second);
};

#endif