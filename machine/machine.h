#ifndef __MACHINE_H
#define __MACHINE_H
#pragma once

#include "../tape/tape.h"
#include "../transition/transition.h"
#include "../state/state.h"

class Machine {
public:
private:
    std::vector<State*> states;
    State currentState;
    Tape tape;
};

#endif