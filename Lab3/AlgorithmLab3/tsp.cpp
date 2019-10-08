#include "tsp.h"
#include <chrono>

TSP::TSP(){}

//take an int value numAlgo to se the selected algoithm
//returns this to allow for chain of responsibilty
TSP* TSP::select(int numAlgo){
    selected = numAlgo;
    return this;
}

//no return type and no parameters
//tracks the time of the selected algorithm
void TSP::run(){
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point end;

    //depending on the selected variable, will choose which TSP algorithm
    //to run ==> 0 = naive implmentation and 1 = dynamic implementation
    if (selected == 0){
        tspAlgo.TSPNaive();
    }
    else if (selected == 1){
        tspAlgo.TSPDynamic();
    }
    else {
        std::cout << "\nNot a valid algorithm." << std::endl;
    }

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(end-start);

    std::cout << "\nTiming :: \t" << time.count() << std::endl;
}
