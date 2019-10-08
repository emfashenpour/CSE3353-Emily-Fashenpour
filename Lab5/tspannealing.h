#ifndef TSPANNEALING_H
#define TSPANNEALING_H
#include <map>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>
#include "math.h"
#include "readfile.h"

class TSPAnnealing {
public:
    TSPAnnealing();

    void simulate();

    TSPAnnealing* setInitialTemp(int);
    TSPAnnealing* decreaseType(int);
    TSPAnnealing* whenToDec(int);
    TSPAnnealing* setInitialTour();

    void createNeighborhood();
    void chooseNeighbor(std::chrono::high_resolution_clock::time_point&,std::chrono::high_resolution_clock::time_point&);
    void decrease();

    float findFitness(std::vector<int>&);

private:
    //readFile object contains: costGraph => a vector of vectors of type cost  (vector<vector<float>> )
    //and the nodes => a map with type int and tuple of float, float, float  (map<int,tuple<float, float, float>>)
    ReadFile nodeData;

    bool accept;
    int time;
    int decType;
    int whenDecType;
    float tempInitial;
    float temperature;
    unsigned long neighborhoodSize;

    std::pair<float, std::vector<int>> bestSol;
    std::pair<float, std::vector<int>> currentSol;
    std::vector<std::pair<float, std::vector<int>>> neighborhood;

};

#endif // TSPANNEALING_H
