#include <iostream>
#include "algofactory.h"

int main()
{
    //enums to show which algorithms there are to choose from
    enum ProblemOptions{TSP = 0, LAST};
    enum TSPOptions{Naive, Dynamic, Tabu, Genetic};
    enum GeneticTabuOptions{ROULETTESEL, ELITESEL, MULTICROS, ONECROS,
                            SWAPMUT, CROSSNEIGH, SWAPNEIGH, NONE};

    AbsAlgorithm* absAlgo = AlgoFactory::create(TSP);
    absAlgo->select(Tabu)->run(SWAPNEIGH, 5, NONE);
    //absAlgo->select(Genetic)->run(ROULETTESEL, MULTICROS, SWAPMUT);
    return 0;
}
