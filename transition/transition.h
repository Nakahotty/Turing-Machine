#ifndef __TRANSITION_H
#define __TRANSITION_H
#pragma once
#include "../state/state.h"

class Transition {
public:
private:
    char read,write,cmd;
    std::vector<State*> states;
};

#endif