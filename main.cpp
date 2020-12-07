#include "machine/machine.cpp"
#include "tape/tape.cpp"
#include "state/state.cpp"
#include "transition/transition.cpp"

int main() {
    DLL<int> list;
    list.push(1);
    list.push(2);
    list.push(3);
    list.push(4);
    list.print();
}