#include "tspannealing.h"
#include <random>
#include <cmath>
#include <chrono>

//constructor initialzes the map of nodes/positions and the cost graph
TSPAnnealing::TSPAnnealing(){
    temperature = 0, decType = 0, whenDecType = 0, accept = false, time = 1;
    nodeData.readData();
    nodeData.fillCostGraph();
    neighborhoodSize = (nodeData.nodes.size() * nodeData.nodes.size());
}

//will continue to traverse the space until temperature is equal to zero
void TSPAnnealing::simulate(){
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point end;

    while (temperature > 0){
        createNeighborhood();

        chooseNeighbor(start, end);

        decrease();

        neighborhood.clear();
    }

    //prints the best path found and its cost
    for (unsigned long i = 0; i < bestSol.second.size(); i++){
        std::cout << bestSol.second[i] + 1 << " => ";
    }
    std::cout << "  Dist:: " << bestSol.first << std::endl;
}

//sets the initial temperature
TSPAnnealing* TSPAnnealing::setInitialTemp(int num){
    temperature = num * nodeData.nodes.size();
    tempInitial = temperature;
    return this;
}

//sets the value of the decrease type
TSPAnnealing* TSPAnnealing::decreaseType(int num){
    decType = num;
    return this;
}

//sets the variable when to decrement
TSPAnnealing* TSPAnnealing::whenToDec(int num){
    whenDecType = num;
    return this;
}

//creates initial solution and sets that value to the best and current solution
TSPAnnealing* TSPAnnealing::setInitialTour(){
    std::vector<int> temp;
    for (unsigned long i = 0; i < nodeData.nodes.size(); i++)
        temp.push_back(i);
    temp.push_back(0);

    std::random_shuffle(temp.begin() + 1, temp.end() - 1);
    currentSol = std::make_pair(findFitness(temp), temp);

    bestSol = currentSol;

    return this;
}

//creates the neighborhood by swapping a elements in the current solution
void TSPAnnealing::createNeighborhood(){
    int first = 0, second = 0, tempI = 0, numToSwap = 0;
    std::vector<int> tempSol;

    //for getting the random index to swap in the solution
    std::random_device seed;
    std::default_random_engine rando(seed());
    std::uniform_int_distribution<int> getRange(1, currentSol.second.size() - 2);

    //generates a neoghborhood the size of the number of nodes squared
    for (unsigned long i = 0; i < neighborhoodSize ; i++){
        //there will be two swaps performed on the initial solution to create neighbors
        numToSwap = nodeData.nodes.size() / 3;
        tempSol = currentSol.second;
        while(numToSwap > 0){
            first = getRange(rando);
            second = getRange(rando);
            tempI = tempSol[first];
            tempSol[first] = tempSol[second];
            tempSol[second] = tempI;
            numToSwap--;
        }
        //adds the neighbor to the neighborhood
        neighborhood.push_back(std::make_pair(findFitness(tempSol), tempSol));
    }
}

//chooses a neighbor to move to at random in the neighborhood
//if the rando has a better fitness than the current, then current is set
//to that solution, else, based on a probability, current will be set to a
//worse solution. Also checks to see if the rando is the best sol so far
void TSPAnnealing::chooseNeighbor(std::chrono::high_resolution_clock::time_point &start, std::chrono::high_resolution_clock::time_point &end){
    int neighIndex = 0;
    float prob = 0, p = 0;;
    std::random_device seed;
    std::default_random_engine rando(seed());
    std::uniform_int_distribution<int> getSol(0, neighborhoodSize - 1);
    std::uniform_real_distribution<float> getProb(0, 1);

    neighIndex = getSol(rando);
    //check to see if the rando solution is better than the current
    if (neighborhood[neighIndex].first < currentSol.first){
        currentSol = neighborhood[neighIndex];
    }

    //if solution is worse, determine the probability that the worse sol is chosen
    else {
        p = exp((-1) * ((neighborhood[neighIndex].first - currentSol.first) / temperature));
        prob = getProb(rando);
        if (prob <= p){
            accept = true;
            currentSol = neighborhood[neighIndex];
        }
    }

    //check to see if the current sol is the best solution found so far
    if (currentSol.first < bestSol.first){
        bestSol = currentSol;
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(end-start);
        std::cout << "\nTiming :: \t" << time.count() << std::endl;
        std::cout << "  Dist:: " << bestSol.first << std::endl;
    }
}

//enum SwarmAnnealOptions{EXPONENTIAL, LINEARLY, EVERY, WORSE};
//this function handles how and when the temperature is decreased
void TSPAnnealing::decrease(){
    //whenDecType = 2 = decrease temp after each iteration
    if (whenDecType == 2){
        //decType = 0 = decrease temperature exponentialy
        if (decType == 0){
            temperature = (int)(tempInitial * std::exp( (-1.0 / ((float)(nodeData.nodes.size()) * 100.0)) * time ) - 1);
        }
        //decType = 1 = decrease temperature linearly
        else if (decType == 1){
            temperature--;
        }
        time++;
    }
    //whenDecType = 3 = decrease temp when a worse solution was accepted
    else if (whenDecType == 3){
        if (accept == true){
            accept = false;
            //decType = 0 = decrease temperature exponentialy
            if (decType == 0){
                temperature = (int)(tempInitial * std::exp( (-1.0 / ((float)(nodeData.nodes.size()) * 100.0)) * time ) - 1);
            }
            //decType = 1 = decrease temperature linearly
            else if (decType == 1){
                temperature--;
            }
            time++;
        }
    }
}

//with find the total distance traveled of a path
float TSPAnnealing::findFitness(std::vector<int> &path){
    float dist = 0;
    for (unsigned int i = 0; i < path.size() - 1; i++)
        dist += nodeData.costGraph[path[i]][path[i + 1]];
    return dist;

}
