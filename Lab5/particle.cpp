#include "particle.h"
#include <random>
#include <cmath>

//constructor
Particle::Particle(){
    neighborhoodSize = 0;
    nodeData.readData();
    nodeData.fillCostGraph();

    //need to set the original velocity vector
    for (unsigned long i = 0; i < localBest.second.size(); i++)
        velocity.push_back(0);

    //need to set initial position vector (initial solution)
    for (unsigned long i = 0; i < nodeData.nodes.size(); i++)
        position.push_back(i);
    position.push_back(0);

    std::random_shuffle(position.begin() + 1, position.end() - 1);

    //initializes the local best as the original position
    localBest = std::make_pair(findFitness(position), position);
}

//sets the neighborhood size int
Particle* Particle::setNeighborhoodSize(int num){
    neighborhoodSize = num;
    return this;
}

//using a random swap method to generate a random neighborhood and then
//find the best solution particle in the neighborhood
Particle* Particle::createNeighborhood(){
    int first = 0, second = 0, tempI = 0, swapVal = nodeData.nodes.size() / 2;
    std::vector<int> temp;

    std::random_device seed;
    std::default_random_engine rando(seed());
    std::uniform_int_distribution<int> getRange(1, position.size() - 2);

    //creates the neighborhood to find the best solution
    for (int i = 0; i < neighborhoodSize; i++){
        temp = position;
        for (int s = 0; s < swapVal; s++){
            first = getRange(rando);
            second = getRange(rando);
            tempI = temp[first];
            temp[first] = temp[second];
            temp[second] = tempI;
        }
        //adds the new neighbor to the neighborhood
        neighborhood.push_back(std::make_pair(findFitness(temp), temp));
    }

    findBestNeighbor();
    neighborhood.clear();
    return this;
}

//will find the neighbor with the best solution in the neighborhood
void Particle::findBestNeighbor(){
    localBest = neighborhood[0];
    for (unsigned long i = 0; i < neighborhood.size(); i++){
        if (neighborhood[i].first < localBest.first)
            localBest = neighborhood[i];
    }
}

//calculates the velocity and new position for the particle
void Particle::calculateVelocity(std::pair<float, std::vector<int>> &globalBest, int cOne, int cTwo, int vMax, std::chrono::high_resolution_clock::time_point& start, std::chrono::high_resolution_clock::time_point& end){
    //using the equation to calculate the velocity and make the particles swarm
    // v = v0 + (cOne * rand1 * (xlocal - x)) + (cTwo * rand2 * (xglobal - x))
    std::random_device seed;
    std::default_random_engine rando(seed());
    std::uniform_real_distribution<float> getRand(0, 1);
    std::uniform_int_distribution<int> getIndex(1, globalBest.second.size() - 2);

    int indexOne = 1, indexTwo = 1, randomI = 0, tempI = 0;
    float randOne = getRand(rando), randTwo = getRand(rando), magnitude = 0;

    std::vector<int> velCalc;

    //calculating the velocity
    velCalc = ((cOne*randOne)*(localBest.second - position)) + ((cTwo*randTwo)*(globalBest.second - position));

    for (unsigned long i = 0; i < velCalc.size(); i++)
        magnitude += velCalc[i] * velCalc[i];

    magnitude = std::sqrt(magnitude);

    velCalc = vMax * velCalc;
    velCalc = (1/magnitude) * velCalc;

    velocity = velocity + velCalc;

    //finds the indexes of the two largest values in the position vector
    for (unsigned long i = 1; i < velCalc.size() - 1; i++)
        if (velCalc[indexOne] < velCalc[i])
            indexOne = i;
    for (unsigned long i = 1; i < velCalc.size() - 1; i++)
        if (velCalc[indexTwo] < velCalc[i] && indexTwo != indexOne)
            indexTwo = i;

    //swaps the two indexes of the highest values in the velocity vec with two random indexes
    randomI = getIndex(rando);
    tempI = position[randomI];
    position[randomI] = position[indexOne];
    position[indexOne] = tempI;

    randomI = getIndex(rando);
    tempI = position[randomI];
    position[randomI] = position[indexTwo];
    position[indexTwo] = tempI;

    //checks to see if the new solution is better than the global best
    if (findFitness(position) < globalBest.first){
        globalBest = std::make_pair(findFitness(position), position);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(end-start);
        std::cout << "\nTiming :: \t" << time.count() << std::endl;
        std::cout << "  Dist:: " << globalBest.first << std::endl;
    }

}

//with find the total distance traveled of a path
float Particle::findFitness(std::vector<int> &path){
    float dist = 0;
    for (unsigned int i = 0; i < path.size() - 1; i++)
        dist += nodeData.costGraph[path[i]][path[i + 1]];
    return dist;

}

