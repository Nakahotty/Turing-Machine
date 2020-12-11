#include "machine/machine.cpp"
#include "tape/tape.cpp"
#include "state/state.cpp"
#include "transition/transition.cpp"

int main() {
    Tape tape("100ab1101");
    std::cout << tape.read() << std::endl;
    tape.moveLeft();
    tape.moveLeft();
    tape.moveRight();
    std::cout << tape.read() << std::endl;
    tape.printWithCurr();

    // State q0
    // State q1
    // State q2 ... 
    State halt("halt");

    // Transition q01
    // Transition q02
    // Transition q11
    // Transition q12
    // Transition q21
    // Transition q22 ... 

    // TuringMachine m(..., &q0); -> initial state
    // m. add state
    // m. find state and add transition ...
    // ...
    // m. find state and add transition
    // m. add state HALT

    // m.run()

}