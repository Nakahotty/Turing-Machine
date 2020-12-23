#include "machine/machine.cpp"
#include "tape/tape.cpp"
#include "state/state.cpp"
#include "transition/transition.cpp"
#include "operations/operations.cpp"

int main() {
    TuringOperation machineCtrl("00100010");
    machineCtrl.runMachine();
}