#ifndef __OPERATIONS_CPP
#define __OPERATIONS_CPP

#include "operations.h"

void Operations::composition() {
    // Дадено: 2 машини - Т1, Т2; вход - А
    // А = 11011 | Т1(А) -> 00000 | T2(T1(A)) -> XXXXX
    // Композиция: done

    MachineController* ctrl; 
    std::string A = "11010";
    Machine T1(A);
    ctrl->initZeroMachine(T1);
    T1.start();
    std::cout << " First convertion of input" << std::endl;
    T1.print();
    
    std::string converted_A = T1.getTape();
    Machine T2(converted_A);
    ctrl->initXMachine(T2);
    T2.start();
    std::cout << " Second convertion of input" << std::endl;
    T2.print();
}

void Operations::decider() {
    MachineController* ctrl; 
    Machine decider("001101");
    ctrl->initDecider(decider);
    decider.start();
    decider.print();

    Machine first("001101"),second("001101");
    ctrl->initTwoMachines(first, second);
    if (decider.finishedSuccessfuly()) {
        std::cout << "Decider finished SUCCESSFULY!" << std::endl;
        first.start();
        std::cout << first.finishedSuccessfuly() << std:: endl;
        first.print();
    } else {
        std::cout << "Decider did NOT FINISH!" << std::endl;
        second.start();
        std::cout << second.finishedSuccessfuly() << std:: endl;
        second.print();
    }
}

void Operations::loopOverMachine() {
    MachineController* ctrl;
    std::string whileInput("001000"), mainInput("09"); 
    
    Machine whileMachine(whileInput);
    Machine main(mainInput);

    ctrl->initLoopMachines(whileMachine, main);

    whileMachine.print();
    main.print();

    while (!whileMachine.finishedSuccessfuly()) {
        main.iterate();
        whileMachine.iterate();
    }

    std::cout << "Main tape:" << std::endl;
    main.print();
}

#endif