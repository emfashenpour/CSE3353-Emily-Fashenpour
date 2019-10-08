#ifndef PARTICLE_H
#define PARTICLE_H
#include <map>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>
#include "math.h"
#include "readfile.h"

//overloaded vector operators => addition, subtraction, and multiplication
inline std::vector<int> operator+(const std::vector<int> &first, const std::vector<int> &second){
    std::vector<int> result;

    for (unsigned long i = 0; i < first.size(); i++)
        result.push_back(first[i] + second[i]);

    return result;
}

inline std::vector<int> operator-(const std::vector<int> &first, const std::vector<int> &second){
    std::vector<int> result;

    for (unsigned long i = 0; i < first.size(); i++)
        result.push_back(first[i] - second[i]);

    return result;
}

inline std::vector<int> operator*(const float &value, const std::vector<int> &first){
    std::vector<int> result;

    for (unsigned long i = 0; i < first.size(); i++)
        result.push_back(value * first[i]);

    return result;
}

//class to be used in the TSP particle swarm algorithm
class Particle {
public:
    Particle();

    Particle* setNeighborhoodSize(int);
    Particle* createNeighborhood();

    void findBestNeighbor();
    void calculateVelocity(std::pair<float, std::vector<int>>&, int, int, int, std::chrono::high_resolution_clock::time_point&, std::chrono::high_resolution_clock::time_point&);

    float findFitness(std::vector<int>&);

    //public member variables of a particle
    ReadFile nodeData;

    int neighborhoodSize;

    std::vector<int> velocity;
    std::vector<int> position;
    std::pair<float, std::vector<int>> localBest;
    std::vector<std::pair<float, std::vector<int>>> neighborhood;

    friend std::vector<int> operator+(const std::vector<int>&, const std::vector<int>&);
    friend std::vector<int> operator-(const std::vector<int>&, const std::vector<int>&);
    friend std::vector<int> operator*(const int&, const std::vector<int>&);
};

#endif // PARTICLE_H
