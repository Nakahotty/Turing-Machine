#include "machine/machine.cpp"
#include "tape/tape.cpp"
#include "state/state.cpp"
#include "transition/transition.cpp"

int main() {
    // ----- Инициализираме състоянията и преходите ----- //

    State* q0 = new State("q0");
    State* q1 = new State("q1");
    State* q2 = new State("q2");
    State* halt = new State("halt");

    Transition* q01 = new Transition('0', ' ', 'L', q1);
    Transition* q02 = new Transition('1', ' ', 'L', q2);
    Transition* q11 = new Transition('1', '0', 'L', q1);
    Transition* q12 = new Transition('1', '0', 'L', q2);
    Transition* q21 = new Transition('0', '0', 'L', q2);
    Transition* q22 = new Transition('1', '1', 'L', halt);

    // ----- Добавяме състоянията в машината както и преходите между тях ----- //
    
    Machine turing("0010001", q0);
    turing.addState(q0);
    turing.findState("q0")->addTransition(q01);
    turing.findState("q0")->addTransition(q02);
    turing.addState(q1);
    turing.findState("q1")->addTransition(q11);
    turing.findState("q1")->addTransition(q12);
    turing.addState(q2);
    turing.findState("q2")->addTransition(q21);
    turing.findState("q2")->addTransition(q22);

    turing.addState(halt);

    turing.print();
    turing.start();
}