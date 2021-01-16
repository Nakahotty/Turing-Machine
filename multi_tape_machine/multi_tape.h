#ifndef __MULTI_TAPE_H
#define __MULTI_TAPE_H

#include "../machine/machine.cpp"

class MultiTapeMachine {
public:
    MultiTapeMachine(std::vector<Tape>);
    void to_single_tape();
private:
    Machine single_tape;
    std::vector<Tape> tapes;
};

#endif