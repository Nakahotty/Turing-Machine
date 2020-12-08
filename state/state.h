#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <vector>
#include "../transition/transition.h"

class State {
public:
    State();
private:
    std::string name;
    std::vector<Transition*> transitions;
};

#endif