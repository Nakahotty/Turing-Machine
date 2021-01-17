#include "machine/machine.cpp"
#include "tape/tape.cpp"
#include "state/state.cpp"
#include "transition/transition.cpp"
#include "controller/controller.cpp"
#include "operations/operations.cpp"

int main() {
    Operations::runBasicMachine();
    Operations::composition();
    Operations::decider();
    Operations::loopOverMachine();
    Operations::toSingleTape();
}