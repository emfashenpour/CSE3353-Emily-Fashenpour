#include <iostream>
#include "algofactory.h"

int main() {
    //enums to show which algorithms there are to choose from
    enum ProblemOptions{TSP = 0, LAST};
    enum TSPOptions{Naive, Dynamic, Tabu, Genetic, Swarm, Annealing};
    enum GeneticTabuOptions{ROULETTESEL, ELITESEL, MULTICROS, ONECROS,
                            SWAPMUT, CROSSNEIGH, SWAPNEIGH, NONE};
    enum SwarmAnnealOptions{EXPONENTIAL, LINEARLY, EVERY, WORSE};

    AbsAlgorithm* absAlgo = AlgoFactory::create(TSP);
    absAlgo->select(Swarm)->run(20, 500, 3, 5, 8);
    //absAlgo->select(Annealing)->run(10, EXPONENTIAL, WORSE, 0, 0);
    return 0;
}
