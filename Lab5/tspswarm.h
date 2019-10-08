#ifndef TSPSWARM_H
#define TSPSWARM_H
#include <map>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>
#include "math.h"
#include "readfile.h"
#include "particle.h"

class TSPSwarm {
public:
    TSPSwarm();

    void swarm();

    TSPSwarm* setCVals(int, int);
    TSPSwarm* setMaxVel(int);
    TSPSwarm* setNumParticles(int);
    TSPSwarm* setNumIterations(int);

    void findGlobalBest();

private:
    //readFile object contains: costGraph => a vector of vectors of type cost  (vector<vector<float>> )
    //and the nodes => a map with type int and tuple of float, float, float  (map<int,tuple<float, float, float>>)
    ReadFile nodeData;

    int maxVel;
    int cOne;
    int cTwo;
    int numParticles;
    int numIterations;

    std::pair<float, std::vector<int>> globalBest;

    std::vector<Particle> particles;
};

#endif // TSPSWARM_H
