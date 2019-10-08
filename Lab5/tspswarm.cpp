#include "tspswarm.h"
#include <random>

//constructor intializes the node map with positions and the cost graph
TSPSwarm::TSPSwarm(){
    numParticles = 0, numIterations = 0, maxVel = 0, cOne = 0, cTwo = 0;
    nodeData.readData();
    nodeData.fillCostGraph();
}

void TSPSwarm::swarm(){
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point end;

    int count = 0;
    while (count < numIterations){
        for (unsigned long i = 0; i < particles.size(); i++){
            particles[i].createNeighborhood()->calculateVelocity(globalBest, cOne, cTwo, maxVel, start, end);
        }

        count++;
    }

    //prints the best path found and its cost
    for (unsigned long i = 0; i < globalBest.second.size(); i++){
        std::cout << globalBest.second[i] + 1 << " => ";
    }
    std::cout << "  Dist:: " << globalBest.first << std::endl;
}

//sets the cOne and cTwo values that change the weight that the global best
//and local best have on the velocity the swarm moves
TSPSwarm* TSPSwarm::setCVals(int c1, int c2){
    cOne = c1;
    cTwo = c2;
    return this;
}

//sets the max velocity value
TSPSwarm* TSPSwarm::setMaxVel(int max){
    maxVel = max;
    return this;
}

//sets the number of particles the swarm will have and initializes each
//particles neighborhood, local best and velocity
TSPSwarm* TSPSwarm::setNumParticles(int num){
    numParticles = num * nodeData.nodes.size();
    for (int i = 0; i < numParticles; i++){
        Particle particle;
        particle.setNeighborhoodSize(numParticles);
        particles.push_back(particle);
    }
    globalBest = particles[0].localBest;
    findGlobalBest();
    return this;
}

//sets the number of iterations the swarm will have before it stops
TSPSwarm* TSPSwarm::setNumIterations(int num){
    numIterations = num;
    return this;
}


//loops through each particle in the particle vector and compares to its local best
//solution to see if it is a better solution than the global best
void TSPSwarm::findGlobalBest(){
    for (unsigned long i = 0; i < particles.size(); i++){
        if (particles[i].localBest.first < globalBest.first)
            globalBest = particles[i].localBest;
    }
}
