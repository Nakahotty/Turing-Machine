#ifndef TRANSITION_H
#define TRANSITION_H
#include <vector>

class State;

class Transition {
public:
    Transition();
private:
    char read,write,cmd;
    std::vector<State*> states;
};

#endif