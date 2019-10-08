#include "tsptabu.h"
#include <random>

TSPTabu::TSPTabu(){
    tabuIndex = 0;
    //need to initialize the taboo list here based on tabIndexMax
    nodeData.readData();
    nodeData.fillCostGraph();
    //nodeData.printNodes();
    //nodeData.printCostGraph();
}

void TSPTabu::tabu(){

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point end;
    while (tabuIteration > 0){
        //will call the neighborhood definition functions to create neighborhoods
        createNeighborhood();
        getBestNeighbor(start, end);

        //need to clear neighborhood so next neighborhood can be found
        neighborhood.clear();

        //decrement number of iterations in tabu
        tabuIteration--;
    }

    std::cout << "+++++++ Best Solution +++++++" << std::endl;
    for (unsigned long i = 0; i < bestSolution.second.size(); i++){
        std::cout << bestSolution.second[i] << " => ";
    }
    std::cout << "  Dist:: " << bestSolution.first << "  " << std::endl;
}

//to define and set the intial solution to tabu
TSPTabu* TSPTabu::setInitialSolution(){
    //generate the solution and its fitness and set localBest and bestSolution
    //to the original solution so they are initialized
    localBest = randomSetSolution();
    bestSolution= localBest;
    return this;
}

//set the tabuListSize and initialize the tabuList
TSPTabu* TSPTabu::setTabuListSize(int size){
    tabuListSize = size * nodeData.nodes.size();
    std::pair<float, std::vector<int>> temp;
    for (int i = 0; i < tabuListSize; i++)
        tabuList.push_back(temp);
    return this;
}

//sets the neighborhood size and type
TSPTabu* TSPTabu::setNeighborhood(int type, int size){
    neighborhoodType = type;
    neighborhoodSize = nodeData.nodes.size() * size;
    return this;
}

//sets the tabuIteration size
TSPTabu* TSPTabu::setTabuIterationSize(int size){
    tabuIteration = size;
    return this;
}

//randomly generates the original solution by shuffling the nodes to
//a random permatation
std::pair<float, std::vector<int>> TSPTabu::randomSetSolution(){
    //adds initial nodes to the solution vector
    std::pair<float, std::vector<int>> solution;
    for (unsigned long i = 0; i < nodeData.nodes.size(); i++){
        solution.second.push_back(i);
    }
    solution.second.push_back(0);

    //randomly generates a permatation
    std::random_shuffle(solution.second.begin() + 1, solution.second.end() - 1);

    //calculate the fitness of the solution
    solution.first = findFitness(solution.second);
    return solution;
}

//uses the multipoint crossover to create new solutions to be tested
//crosses the the localbest soltion with a randomly generated solution
//and adds to neighborhood until the size is met
void TSPTabu::crossNeighborhood(){
    std::vector<int> parent1 = localBest.second;
    std::vector<int> parent2, child1, child2;
    int child1I = 1, child2I = 1, startIndex = 0, endIndex = 0, ct = 0;
    float setSizeToCross = nodeData.nodes.size() * (25 / 100);
    bool found1 = false, found2 = false;

    std::random_device seed;
    std::default_random_engine rando(seed());
    std::uniform_int_distribution<int> getRange(1, nodeData.nodes.size() - setSizeToCross);

    //initialize the child solution vectors
    for (unsigned long i = 0; i < parent1.size(); i++){
        child1.push_back(0);
        child2.push_back(0);
    }

    startIndex = getRange(rando);
    endIndex = startIndex + setSizeToCross - 1;

    while (neighborhood.size() < neighborhoodSize){
        parent2 = randomSetSolution().second;
        child1I = 1, child2I = 1;

        //begin loop to cross the parents to create the children
        for (unsigned int long i = 1; i < parent1.size() - 1; i++){
            found1 = false, found2 = false;
            for (int c = startIndex; c <= endIndex; c++){
                if (parent1[i] == parent2[c])
                    found1 = true;
                if (parent2[i] == parent1[c])
                    found2 = true;
            }
            if (child1I == startIndex)
                child1I += (endIndex - startIndex) + 1;
            if (child2I >= startIndex)
                child2I += (endIndex - startIndex) + 1;
            if (!found1)
                child2[child2I++] = parent1[i];
            if (!found2)
                child1[child1I++] = parent2[i];
        }

        //adding the remaining nodes not in the child from the parent in the order they are found
        for (int i = 0; i <= endIndex - startIndex; i++){
            child1[startIndex + i] = parent1[startIndex + i];
            child2[startIndex + i] = parent2[startIndex + i];
        }

        //need to calculate the fitness scores for the children, make pair, and add
        //to new population but check to see if the newPopulation is not bigger than population
        neighborhood.push_back(std::make_pair(findFitness(child1), child1));
        ct++;
        if (neighborhood.size() < neighborhoodSize){
            neighborhood.push_back(std::make_pair(findFitness(child2), child2));
            ct++;
        }
    }
}

void TSPTabu::swapNeighborhood(){
    std::pair<float, std::vector<int>> tempSol;
    int swapIndex = 0, tempVal = 0;

    //continue to generate temp solutions until the neighborhood size is met
    while (neighborhood.size() < neighborhoodSize){
        tempSol = localBest;
        std::random_device seed;
        std::default_random_engine rando(seed());
        for (unsigned long i = 1; i < tempSol.second.size() - 1; i++){
            std::uniform_real_distribution<float> getInRange(i, tempSol.second.size() - 1);

            //indexes that will be used in swap are swapIndex and i
            swapIndex = getInRange(rando);
            tempVal = tempSol.second[i];
            tempSol.second[i] = tempSol.second[swapIndex];
            tempSol.second[swapIndex] = tempVal;
        }
        tempSol.first = findFitness(tempSol.second);
        neighborhood.push_back(tempSol);
    }
}

void TSPTabu::createNeighborhood(){
    //if the neighborhoodType equals 5, then run the cross neighborhood method
    if (neighborhoodType == 5)
        crossNeighborhood();
    //if neighborhoodType equals 6, then run the swap neighborhood method
    if (neighborhoodType == 6)
        swapNeighborhood();
}

//will traverse through the neighborhood and find the neighbor solution
//that has the lowest fitness value
void TSPTabu::getBestNeighbor(std::chrono::high_resolution_clock::time_point &start,std::chrono::high_resolution_clock::time_point &end){
    //finds the localBest in a neighborhood
    localBest = neighborhood[0];
    for (unsigned long i = 1; i < neighborhood.size(); i++){
        if (neighborhood[i].first < localBest.first)
            localBest = neighborhood[i];
    }

    //checks to see if the localBest is better than the global best solution
    if (localBest.first < bestSolution.first){
        bestSolution = localBest;
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(end-start);
        std::cout << "\nTiming :: \t" << time.count() << std::endl;
        for (unsigned long i = 0; i < bestSolution.second.size(); i++){
                std::cout << bestSolution.second[i] + 1 << " => ";
            }
            std::cout << "  Dist:: " << bestSolution.first << std::endl;
    }

    //checks to see if the localBest is already in tabu and if not, adds it
    if (!inTabuList())
        addToTabuList(localBest);
}

//adds a solution, which is accepted as a parameter, to the tabu list and then check
//to see if the index is equal to one less than the tabuListSize - 1. Resets the index value
//to zero which will begin to write over the tabuList
void TSPTabu::addToTabuList(std::pair<float, std::vector<int>>& solution){
    tabuList[tabuIndex++] = solution;
    if (tabuIndex == tabuListSize - 1)
        tabuIndex = 0;
}

//returns a boolean of whether or not a solution is already in the tabuList
bool TSPTabu::inTabuList(){
    bool same = true;

    for(int i = 0; i < tabuListSize; i++){
        if (tabuList[i].first == localBest.first){
            for (unsigned long c = 1; c < localBest.second.size() - 1; c++){
                if (tabuList[i].second[c] != localBest.second[c])
                    same = false;
            }
            if (same)
                return true;
        }
    }
    return false;
}

//finds the fitness of a solution (aka finds the distance of a
//given path) returns a float value of distance and accepts a reference
//to a vector of integers
float TSPTabu::findFitness(std::vector<int> &solution){
    float dist = 0;
    for (unsigned int i = 0; i < solution.size() - 1; i++)
        dist += nodeData.costGraph[solution[i]][solution[i + 1]];
    return dist;
}

//prints out all the solutions in the neighborhood
void TSPTabu::printNeighborhood(){
    for (unsigned long i = 0; i < neighborhood.size(); i++){
        for (unsigned long c = 0; c < neighborhood[i].second.size(); c++){
            std::cout << neighborhood[i].second[c] << " => ";
        }
        std::cout << "  Dist:: " << neighborhood[i].first << "  " << i << std::endl;
    }
}
