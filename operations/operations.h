#ifndef __OPERATIONS_H
#define __OPERATIONS_H

#include "../machine/machine.h"

class TuringOperation {
public:
    void initializeStates();
    void initializeTransitions();
    void runMachine();
private:
    Machine machine;
};

class Composition : public TuringOperation {
public:

private:
};

#endif