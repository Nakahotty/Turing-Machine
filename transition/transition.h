#ifndef TRANSITION_H
#define TRANSITION_H
#include <vector>
#include <iostream>

class State;

class Transition {
public:
    Transition(Transition, State*);
    Transition(char, char, char, State*);
    Transition& operator=(const Transition& other);
    State* getNextState();
    char getReadSymbol() const;
    char getWriteSymbol() const;
    char getCommand() const;
    void print() const;
private:
    char read,write,cmd;
    State* state;
};

std::ostream& operator<<(std::ostream& out, Transition& transition);

#endif