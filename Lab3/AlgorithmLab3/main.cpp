#include <iostream>
#include "tspalgorithm.h"
#include "algofactory.h"

int main()
{
    //enums to show which algorithms there are to choose from
    enum AlgorithmsOptions{TSP = 0, LAST};
    enum TSPOptions{TSPNaive, TSPDynamic};

    AbsAlgorithm* absAlgo = AlgoFactory::create(TSP);
    //absAlgo->select(TSPNaive)->run();
    absAlgo->select(TSPDynamic)->run();
    return 0;
}
