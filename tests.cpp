#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "machine/machine.cpp"
#include "tape/tape.cpp"
#include "state/state.cpp"
#include "transition/transition.cpp"
#include "controller/controller.cpp"
#include "operations/operations.cpp"

TEST_CASE("Basic Machine Run Test") {
    CHECK(0 == 0);
}

TEST_CASE("Composition of two Turing Machines") {
    MachineController* ctrl; 
    std::string A, directory("./txt/composition/tapes.txt");
    ctrl->readSingleTape(A,directory);

    // Tape read 
    CHECK(A == "11010"); 

    Machine T1(A);
    ctrl->initZeroMachine(T1);

    // States read
    CHECK(T1.findState("init") != nullptr);
    CHECK(T1.findState("to zero") != nullptr);

    // Transitions read
    T1.findState("init")->hasTransition('0');
    T1.findState("init")->hasTransition('1');
    T1.findState("to zero")->hasTransition('0');
    T1.findState("to zero")->hasTransition('1');
    T1.findState("to zero")->hasTransition('_');

    T1.start();
    CHECK(T1.finishedSuccessfuly());

    std::string converted_A = T1.getTape();
    CHECK(converted_A == "00000");

    Machine T2(converted_A);
    ctrl->initXMachine(T2);

    // States read
    CHECK(T2.findState("init") != nullptr);
    CHECK(T2.findState("X") != nullptr);

    // Transitions read
    T2.findState("init")->hasTransition('0');
    T2.findState("init")->hasTransition('1');
    T2.findState("X")->hasTransition('0');
    T2.findState("X")->hasTransition('1');
    T2.findState("X")->hasTransition('_');

    T2.start();
    CHECK(T2.getTape() == "XXXXX");
}

TEST_CASE("Branching of two Turing Machines depending on decider") {
    MachineController* ctrl; 

    std::string tape, location("./txt/decider/tapes.txt");
    ctrl->readSingleTape(tape, location);

    Machine decider(tape);
    ctrl->initDecider(decider);

    // Tape read
    CHECK(decider.getTape() == "001101");

    // States read
    CHECK(decider.findState("init") != nullptr);
    CHECK(decider.findState("halt") != nullptr);
    CHECK(decider.findState("reject") != nullptr);

    // Transitions read
    decider.findState("init")->hasTransition('0');
    decider.findState("init")->hasTransition('1');

    decider.start();

    Machine first(tape),second(tape);
    ctrl->initTwoMachines(first, second);

    // Tape read
    CHECK(first.getTape() == "001101");
    CHECK(second.getTape() == "001101");

    // States read
    CHECK(first.findState("init") != nullptr);
    CHECK(first.findState("q1") != nullptr);
    CHECK(second.findState("init") != nullptr);
    CHECK(second.findState("q0") != nullptr);

    // Transitions read
    CHECK(first.findState("init")->hasTransition('0'));
    CHECK(first.findState("init")->hasTransition('1'));
    CHECK(first.findState("q1")->hasTransition('0'));
    CHECK(first.findState("q1")->hasTransition('1'));
    CHECK(first.findState("q1")->hasTransition('_'));

    CHECK(second.findState("init")->hasTransition('0'));
    CHECK(second.findState("init")->hasTransition('1'));
    CHECK(second.findState("q0")->hasTransition('0'));
    CHECK(second.findState("q0")->hasTransition('1'));
    CHECK(second.findState("q0")->hasTransition('_'));

    if (decider.finishedSuccessfuly()) {
        first.start();
        CHECK(first.finishedSuccessfuly());
    } else {
        second.start();
        CHECK(second.finishedSuccessfuly());
    }
}


TEST_CASE("Machine that runs a while-cycle over given Turing Machine") {
    MachineController* ctrl;
    
    std::vector<std::string> tapes;
    std::string location("./txt/loop/tapes.txt");
    ctrl->readMultiTape(tapes, location);

    Machine whileMachine(tapes[0]);
    Machine main(tapes[1]);

    ctrl->initLoopMachines(whileMachine, main);

     // Tape read
    CHECK(whileMachine.getTape() == "001000");
    CHECK(main.getTape() == "09");

    // States read
    CHECK(whileMachine.findState("init") != nullptr);
    CHECK(whileMachine.findState("halt") != nullptr);
    CHECK(whileMachine.findState("searchOne") != nullptr);
    CHECK(main.findState("init") != nullptr);
    CHECK(main.findState("halt") != nullptr);
    CHECK(main.findState("addChar") != nullptr);

    // Transitions read
    CHECK(whileMachine.findState("init")->hasTransition('0'));
    CHECK(whileMachine.findState("init")->hasTransition('1'));
    CHECK(whileMachine.findState("searchOne")->hasTransition('0'));
    CHECK(whileMachine.findState("searchOne")->hasTransition('1'));

    CHECK(main.findState("init")->hasTransition('0'));
    CHECK(main.findState("init")->hasTransition('1'));
    CHECK(main.findState("addChar")->hasTransition('0'));
    CHECK(main.findState("addChar")->hasTransition('9'));
    CHECK(main.findState("addChar")->hasTransition('_'));

    while (!whileMachine.finishedSuccessfuly()) {
        main.iterate();
        whileMachine.iterate();
    }

    CHECK(whileMachine.finishedSuccessfuly());
}

TEST_CASE("Multi tape Turing Machine transforming into single tape") {
    CHECK(0 == 0);
}

int main() {
    doctest::Context().run();
}