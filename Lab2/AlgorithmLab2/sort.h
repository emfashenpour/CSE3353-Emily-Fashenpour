#ifndef SORT_H
#define SORT_H
#include "sortalgorithm.h"
#include "algorithm.h"
#include "datacreator.h"
#include <chrono>

//derived class of Algorithm that will
//call sortAlgorithm functions
class Sort: public Algorithm{
public:
    Sort();
    void load(char*);
    void execute();
    void display();
    void stats();
    void select(int);
    void save(char*);
    void configure();
private:
    SortAlgorithm sorter;
    std::vector<int> currentSet;
    std::vector<double> timeStat;
    int currentAlgo;
};

#endif // SORT_H
