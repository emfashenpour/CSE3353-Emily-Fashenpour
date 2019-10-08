#include "algofactory.h"
#include <iostream>
#include "tsp.h"

AlgoFactory::AlgoFactory(){}

//returns an AbsAlgorithm pointer
//the algoNum int will determine which derived algorithm class
//is returned
AbsAlgorithm* AlgoFactory::create(int algoNum){
    //initially sets the algorithm pointer to null
    AbsAlgorithm* algorithm = nullptr;

    //algoNum corresponds to a derived algo class name
    //=> 0 = TSP derived class
    if (algoNum == 0){
        algorithm = new TSP();
    }
    else {
        std::cout << "\nNot a valid algorithm." << std::endl;
    }
    return algorithm;
}
