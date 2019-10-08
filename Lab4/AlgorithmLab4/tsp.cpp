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
void TSP::run(int first, int second, int third){
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point end;

    //depending on the selected variable, will choose which TSP algorithm
    //to run ==> 0 = naive implmentation, 1 = dynamic implementation
    // 2 = tabu search algorithm, and 3 = genetic search algorithm
    if (selected == 0){
        //TSPAlgoroithm tspAlgoNaive;
        //tspAlgoNaive.TSPNaive();
    }
    else if (selected == 1){
        //TSPAlgoroithm tspAlgoDyn;
        //tspAlgoDyn.TSPDynamic();
    }
    else if (selected == 2){
        TSPTabu tspTab;
        tspTab.setInitialSolution()->setNeighborhood(first, 6)->setTabuIterationSize(400000)->setTabuListSize(second)->tabu();
    }
    else if (selected == 3){
        TSPGenetic tspGen;
        tspGen.setSelectionType(first,50)->setNumGeneration(10000)->setCrossoverType(second, 50)->setMutation(third, 5, 1)->setInitialPopulation(10)->genetic();
    }
    else {
        std::cout << "\nNot a valid algorithm option to select." << std::endl;
    }

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(end-start);

    std::cout << "\nTiming :: \t" << time.count() << std::endl;
}
