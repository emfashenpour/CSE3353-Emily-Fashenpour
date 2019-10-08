#ifndef TSPGENETIC_H
#define TSPGENETIC_H
#include <map>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>
#include "math.h"
#include "readfile.h"

class TSPGenetic{
public:
    TSPGenetic();

    void genetic();

    TSPGenetic* setInitialPopulation(int);
    TSPGenetic* setNumGeneration(int);
    TSPGenetic* setSelectionType(int, int);
    TSPGenetic* setCrossoverType(int, int);
    TSPGenetic* setMutation(int,float,int);

    void rouletteSelection(float&);
    void eliteSelection(float&);
    void multiPtCrossover(float&);
    void onePtCrossover(float&);
    void swapMutate();
    void selection(float&);
    void crossover(float&);
    void mutate();

    float findFitness(std::vector<int>&);
    void findBestPath(std::chrono::high_resolution_clock::time_point&,std::chrono::high_resolution_clock::time_point&);
    void printPopulation();


private:
    //readFile object contains: costGraph => a vector of vectors of type cost  (vector<vector<float>> )
    //and the nodes => a map with type int and tuple of float, float, float  (map<int,tuple<float, float, float>>)
    ReadFile nodeData;

    int selectionType;
    float selectPerc;
    int crossoverType;
    float crossPerc;
    int mutateType;
    float mutationPercentage;
    int swapMutVal;
    int generation;
    int stopGeneration;

    std::pair<float, std::vector<int>> bestPath;

    std::vector<std::pair<float, std::vector<int>>> population;
    std::vector<std::pair<float, std::vector<int>>> newPopulation;


};

#endif // TSPGENETIC_H
