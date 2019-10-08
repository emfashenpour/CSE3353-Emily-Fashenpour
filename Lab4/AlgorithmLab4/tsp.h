#ifndef TSP_H
#define TSP_H
#include "absalgorithm.h"
#include "tspgenetic.h"
#include "tsptabu.h"


//child class of the Abstract Algorithm class that implements
//the select and run methods
//uses the chain of responsibility design pattern
class TSP: public AbsAlgorithm{
private:
    //selected variable tracks the algorithm to run
    int selected;
public:
    TSP();
    TSP* select(int);
    void run(int, int, int);
};

#endif // TSP_H
