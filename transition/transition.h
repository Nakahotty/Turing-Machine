#ifndef TRANSITION_H
#define TRANSITION_H
#include <vector>

class State;

class Transition {
public:
    Transition(char, char, char, State*);
    State* getNextState();
    char getReadSymbol() const;
    char getWriteSymbol() const;
    char getCommand() const;
private:
    char read,write,cmd;
    State* state;
};

#endif