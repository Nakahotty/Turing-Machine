#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <vector>
#include "../transition/transition.h"

class State {
public:
    State(const std::string& name);
    State& operator=(const State&);
    
    std::string getName() const;
    void addTransition(Transition*);
    bool hasTransition(const char& input);
    Transition* getTransition(const char& input);
private:
    std::string name;
    std::vector<Transition*> transitions;
};

std::ostream& operator<<(std::ostream& out, State& state);

#endif