#ifndef TSPTABU_H
#define TSPTABU_H
#include <map>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>
#include "math.h"
#include "readfile.h"

class TSPTabu{
public:
    TSPTabu();

    void tabu();

    TSPTabu* setInitialSolution();
    TSPTabu* setTabuListSize(int);
    TSPTabu* setNeighborhood(int, int);
    TSPTabu* setTabuIterationSize(int);

    std::pair<float, std::vector<int>> randomSetSolution();
    void crossNeighborhood();
    void swapNeighborhood();
    void createNeighborhood();

    void getBestNeighbor(std::chrono::high_resolution_clock::time_point&,std::chrono::high_resolution_clock::time_point&);
    void addToTabuList(std::pair<float, std::vector<int>>&);
    bool inTabuList();
    float findFitness(std::vector<int>&);
    void printNeighborhood();

private:
    //readFile object contains: costGraph => a vector of vectors of type cost  (vector<vector<float>> )
    //and the nodes => a map with type int and tuple of float, float, float  (map<int,tuple<float, float, float>>)
    ReadFile nodeData;

    int tabuIndex;
    int tabuListSize;
    int tabuIteration;
    int neighborhoodType;
    unsigned long neighborhoodSize;

    std::pair<float, std::vector<int>> bestSolution;
    std::pair<float, std::vector<int>> localBest;
    std::vector<std::pair<float, std::vector<int>>> tabuList;
    std::vector<std::pair<float, std::vector<int>>> neighborhood;

};

#endif // TSPTABU_H
