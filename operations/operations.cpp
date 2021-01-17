#ifndef __OPERATIONS_CPP
#define __OPERATIONS_CPP

#include "operations.h"

void Operations::composition() {
    // Дадено: 2 машини - Т1, Т2; вход - А
    // А = 11011 | Т1(А) -> 00000 | T2(T1(A)) -> XXXXX

    MachineController* ctrl; 
    std::string A, directory("./txt/composition/tapes.txt");
    ctrl->readSingleTape(A,directory);
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

    std::string tape, location("./txt/decider/tapes.txt");
    ctrl->readSingleTape(tape, location);

    Machine decider(tape);
    ctrl->initDecider(decider);
    decider.start();
    decider.print();

    Machine first(tape),second(tape);
    ctrl->initTwoMachines(first, second);
    if (decider.finishedSuccessfuly()) {
        std::cout << "Decider finished SUCCESSFULY!" << std::endl;
        first.start();

        if(first.finishedSuccessfuly())
            first.print();
    } else {
        std::cout << "Decider did NOT FINISH!" << std::endl;
        second.start();
        
        if(second.finishedSuccessfuly())
            second.print();
    }
}

void Operations::loopOverMachine() {
    MachineController* ctrl;
    
    std::vector<std::string> tapes;
    std::string location("./txt/loop/tapes.txt");
    ctrl->readMultiTape(tapes, location);

    Machine whileMachine(tapes[0]);
    Machine main(tapes[1]);

    ctrl->initLoopMachines(whileMachine, main);

    whileMachine.print();
    main.print();

    while (!whileMachine.finishedSuccessfuly()) {
        main.iterate();
        whileMachine.iterate();
    }

    if (main.finishedSuccessfuly()) {
        std::cout << "Main tape:" << std::endl;
        main.print();
    }
}

void Operations::toSingleTape() {
    // Transforming multiple machines into one

    MachineController* ctrl;

    std::vector<std::string> tapes;
    std::string location("./txt/multi/tapes.txt");
    ctrl->readMultiTape(tapes, location);

    Machine main;
    std::vector<Machine> machines;
    size_t size = tapes.size(); 
    for(size_t i = 0; i < size; i++) {
        Machine m(tapes[i]);
        machines.push_back(m);
    }
    
    ctrl->initMultiMachine(main,machines);

    main.start();
    
    if (main.finishedSuccessfuly()) {
        std::cout << "Converted multitape successfuly" << std::endl; 
        main.print();
    }
}

#endif