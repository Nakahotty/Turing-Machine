#include "machine/machine.cpp"
#include "tape/tape.cpp"
#include "state/state.cpp"
#include "transition/transition.cpp"

int main() {
    Tape tape("1001101");
    tape.print();
    std::cout << tape.read() << std::endl;
    tape.moveLeft();
    tape.moveLeft();
    std::cout << tape.read() << std::endl;
    tape.printWithCurr();
}