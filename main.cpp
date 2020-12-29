#include "machine/machine.cpp"
#include "tape/tape.cpp"
#include "state/state.cpp"
#include "transition/transition.cpp"
#include "controller/controller.cpp"

int main() {
    MachineController ctrl("00100010");
    ctrl.runMachine();
}