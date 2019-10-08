#ifndef READFILE_H
#define READFILE_H
#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <fstream>
#include "math.h"


//class that reads in data from a "positions.txt" file
//utilized in the TSPAlgorithm class
class ReadFile {
public:
    ReadFile();
    void readData();
    void fillCostGraph();
    float distanceFrom(int, int);
    void printNodes();
    void printCostGraph();

    //kept public so there is easy access
    std::map<int, std::tuple<float, float, float>> nodes;
    std::vector<std::vector<float>> costGraph;
};

#endif // READFILE_H
