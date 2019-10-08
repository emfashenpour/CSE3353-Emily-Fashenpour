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
class ReadFile
{
public:
    ReadFile();
    std::map<int, std::tuple<float, float, float>>& readData();
private:
    std::map<int, std::tuple<float, float, float>> nodes;
};

#endif // READFILE_H
