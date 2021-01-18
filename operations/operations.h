#ifndef __OPERATIONS_H
#define __OPERATIONS_H

#include "../machine/machine.h"
#include "../controller/controller.h"

class Operations {
public: 
    static void composition();
    static void decider();
    static void loopOverMachine();
    static void toSingleTape();
    static void basicMachine();
    static void runConsole();
};

#endif