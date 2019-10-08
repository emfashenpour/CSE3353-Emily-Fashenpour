#ifndef TSPALGORITHM_H
#define TSPALGORITHM_H
#include <map>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>
#include "math.h"
#include "readfile.h"

#define MAX 0x3f3f3f3f


//class implements the dynamic and naive algorithm of the
//traveling salesman problem (hamiltonian circuit)
class TSPAlgorithm
{
private:
    ReadFile fileData;
    std::map<int, std::tuple<float, float, float>> nodes;
    std::vector<std::vector<float>> costGraph;

    //variables used for naive implmentation
    std::vector<std::vector<float>> paths;
    int indexShortest;
    unsigned int totalPaths;

public:
    TSPAlgorithm();
    void TSPNaive();
    void naiveRecur(int, int, std::vector<bool>, std::vector<float>&, int&);
    void TSPDynamic();
    std::pair<float, std::vector<int>> dynamRecur(int, int, int, std::vector<int>, int&);
    void fillCostGraph();
    void totalPathsToFind();
    bool allVisited(std::vector<bool>&);
    float distanceFrom(int, int);
    void findTotalDistance();
    void printNodes();
    void printCostGraph();
    void printNaivePaths();
    void printNaiveShortestPath();
};

#endif // TSPALGORITHM_H
