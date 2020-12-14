#ifndef STATE_CPP
#define STATE_CPP

#include "state.h"

State::State(const std::string& name) {
    this->name = name;
}

    
std::string State::getName() const {
    return name;
}

void State::addTransition(Transition* trans) {
    transitions.push_back(trans);
}

bool State::hasTransition(const char& input) {
    for(std::vector<Transition*>::iterator it = transitions.begin(); it != transitions.end(); ++it) {
        // if ((*it)->getReadSymbol() == input)
            return true;
    }

    return false;
}

Transition* State::getTransition(const char& input) {
    for(std::vector<Transition*>::iterator it = transitions.begin(); it != transitions.end(); ++it) {
        Transition* curr = *it;
        if (curr->getReadSymbol() == input)
            return curr;
    }

    return nullptr;
}

std::ostream& operator<<(std::ostream& out, State& state) {
    out << '{' << state.getName() << '}';
    return out;
}

#endif
