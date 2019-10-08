#ifndef TSP_H
#define TSP_H
#include "absalgorithm.h"
#include "tspalgorithm.h"


//child class of the Abstract Algorithm class that implements
//the select and run methods
//uses the chain of responsibility design pattern
class TSP: public AbsAlgorithm{
private:
    //selected variable tracks the algorithm to run
    int selected;
    TSPAlgorithm tspAlgo;
public:
    TSP();
    TSP* select(int);
    void run();
};

#endif // TSP_H
