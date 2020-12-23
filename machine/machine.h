#ifndef MACHINE_H
#define MACHINE_H

#include "../tape/tape.h"
#include "../transition/transition.h"
#include "../state/state.h"
#include <fstream>

class Machine {
public:
    Machine();
    Machine(const std::string&, State*);
    Machine(const Machine&);
    Machine& operator=(const Machine&);

    void addState(State*);
    State* findState(const std::string&);
    bool isThereState(const std::string&);
    void setCurrentState(State*);
    void setTape(const std::string&);
    
    void print();
    void iterate();
    void start();

    bool finishedSuccessfuly() const;
private:
    std::vector<State*> states; // всички състояния заданени на машината
    State* currentState; // текущото
    Tape tape;

    std::string fileName;
    std::ofstream out;

    void copy(const Machine&);
};

#endif