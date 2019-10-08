#include "tspgenetic.h"
#include <random>
#include <chrono>

//constructor, initializes variables, node map in the FileRead class
//and also the cost graph
TSPGenetic::TSPGenetic(){
   selectionType = 0, crossoverType = 0, mutationPercentage = 0, mutateType = 0;;
   crossPerc = 0, selectPerc = 0, generation = 0;
   nodeData.readData();
   nodeData.fillCostGraph();
}

//method where the generations are created and the bestPath is found
void TSPGenetic::genetic(){
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point end;
    float selectCount = population.size() * (selectPerc / 100);
    float crossCount = population.size() * (crossPerc / 100);

    while (generation < stopGeneration){
        //this is where the newPopulation is determined and created by calling
        //the selection, crossover, and mutate methods
        selection(selectCount);
        crossover(crossCount);
        mutate();

        //find the best path in the current generation
        findBestPath(start, end);


        //setting the population to the newPopulation so next generation
        //can be found and clears newPopulation so the next newPop can be added
        population = newPopulation;
        newPopulation.clear();
        generation++;
    }

    //prints the best path and its cost
    for (unsigned long i = 0; i < bestPath.second.size(); i++){
        std::cout << bestPath.second[i] + 1 << " => ";
    }
    std::cout << "  Dist:: " << bestPath.first << std::endl;
}

//sets the initial population to perform the genetic algorithm on
//accepts an int value that will determine the size of the population
//population = # of nodes times the integer value
//Returns a TSPGenetic object pointer
TSPGenetic* TSPGenetic::setInitialPopulation(int mul){
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point end;
    std::vector<int> tempPath;
    for (unsigned long i = 0; i < nodeData.nodes.size(); i++){
        tempPath.push_back(i);
    }
    tempPath.push_back(0);

    for (unsigned long i = 0; i < nodeData.nodes.size() * mul; i++){
        std::random_shuffle(tempPath.begin() + 1, tempPath.end() - 1);
        population.push_back(std::make_pair(findFitness(tempPath), tempPath));
    }

    //temporarily set best path so that it can be compared in the findBestPath function
    bestPath = population[0];
    findBestPath(start, end);

    //divides the mutationPercentage
    mutationPercentage /= 100;
    //printPopulation();
    return this;
}

//set the number of generations there will be. Used as the stopping case
TSPGenetic* TSPGenetic::setNumGeneration(int size){
    stopGeneration = size;
    return this;
}

//sets the selection type that will be used when creating a new generation
//Returns a TSPGenetic object pointer and accepts an int value to determine
//selection type and a float value for the percentage of the population
//that will be selected and added to the newPopulation
TSPGenetic* TSPGenetic::setSelectionType(int type, int perc){
    selectionType = type;
    selectPerc = perc;
    return this;
}

//set the crossover method to be used when creating the newPopulation
//Returns a TSPGenetic object pointer and accepts an int value to determine
//crossover type and a float value for the percentage of the population
//that will be crossed over
TSPGenetic* TSPGenetic::setCrossoverType(int type, int perc){
    crossoverType = type;
    crossPerc = perc;
    return this;
}

//set the percentage of the population that needs to be mutated
//each generation. Returns a TSPGenetic object pointer and
//accepts a float value for the percent
TSPGenetic* TSPGenetic::setMutation(int type, float percent, int swap){
    mutateType = type;
    mutationPercentage = percent;
    swapMutVal = swap;
    return this;
}

//roulette selection adds a solution to the newPopulation based on the probability
//determined by dividing its fitness score by the sum of all the fitness scores
//and adding that value to a corresponding vector
void TSPGenetic::rouletteSelection(float &count){
    std::vector<float> p;
    float fitnessSum = 0, pVal = 0, tempP = 0;
    unsigned long ind = 0;

    //find the sum of all the fitness values
    for (unsigned long i = 0; i < population.size(); i++)
        fitnessSum += findFitness(population[i].second);

    //assigned the p vector with a value of the fitness/fitnessSum
    for (unsigned long i = 0; i < population.size(); i++){
        tempP = population[i].first / fitnessSum;
        pVal += tempP;
        p.push_back(pVal);
    }

    //need to generate a random value between 0 and 1
    while (newPopulation.size() < count){
        std::random_device seed;
        std::default_random_engine rando(seed());
        std::uniform_real_distribution<float> getDistri(0,1);
        float randP = getDistri(rando);

        //adds the solution at the randomly generated valP index of
        //population to the newPopulation vector.
        if (randP <= p[ind])
            newPopulation.push_back(population[ind]);
        ind++;
        if (ind == p.size())
            ind = 0;
    }
}

//elite selection adds count solutions to the newPopulation. After sorting,
//will add the solutions with the smallest fitness values to the newPopulation
void TSPGenetic::eliteSelection(float &count){
    //copies population into temp population to be sorted so the original pop in not changed
    std::vector<std::pair<float, std::vector<int>>> tempPop = population;

    //sorts the tempPop vector by its fitness value so the best solutions are at the beginning
    std::sort(tempPop.begin(), tempPop.end());

    //adds count solutions to the new population
    for (int i = 0; i < count; i++){
        newPopulation.push_back(tempPop[i]);
    }

}

//generates two new children based on two randomly selected parents from the population
//calculates the children's fitness scores and then adds them to the new population
//children generated using ordered multi point crossover => selects a random start index
//and the size to move from parent to child, then copies the missing nodes from child
//in order found in 2nd parent
void TSPGenetic::multiPtCrossover(float &count){
    int start = 0, end = 0, parent1 = 0, parent2 = 0, ct = 0;
    int childOneI = 1, childTwoI = 1;
    bool foundOne = false, foundTwo = false;

    //initialize the children to be the size of the parent vector path
    std::vector<int> childOne;
    std::vector<int> childTwo;
    for (unsigned long i = 0; i < population[0].second.size(); i++){
        childOne.push_back(0);
        childTwo.push_back(0);
    }

    float percToCross = 25;
    int numToCross = nodeData.nodes.size() * (percToCross / 100);

    std::random_device seed;
    std::default_random_engine rando(seed());

    //will find a random start spot for the crossover
    std::uniform_int_distribution<int> getChroRange(1, nodeData.nodes.size() - numToCross);

    //will find a random number between 0 and the population size to find random parent
    std::uniform_int_distribution<int> getPopRange(0, population.size() - 1);
    start = getChroRange(rando);
    end = start + numToCross - 1;

    while (ct < count){
        //find the parent index to cross from population
        parent1 = getPopRange(rando);
        parent2 = getPopRange(rando);
        childOneI = 1, childTwoI = 1;

        //begin loop to cross the parents to create the children
        for (unsigned int long i = 1; i < population[0].second.size() - 1; i++){
            foundOne = false, foundTwo = false;
            for (int c = start; c <= end; c++){
                if (population[parent1].second[i] == population[parent2].second[c])
                    foundOne = true;
                if (population[parent2].second[i] == population[parent1].second[c])
                    foundTwo = true;
            }
            if (childOneI == start)
                childOneI += (end - start) + 1;
            if (childTwoI == start)
                childTwoI += (end - start) + 1;
            if (!foundOne)
                childTwo[childTwoI++] = population[parent1].second[i];
            if (!foundTwo)
                childOne[childOneI++] = population[parent2].second[i];
        }

        //adding the remaining nodes not in the child from the parent in the order they are found
        for (int i = 0; i <= end - start; i++){
            childOne[start + i] = population[parent1].second[start + i];
            childTwo[start + i] = population[parent2].second[start + i];
        }

        //need to calculate the fitness scores for the children, make pair, and add
        //to new population but check to see if the newPopulation is not bigger than population
        newPopulation.push_back(std::make_pair(findFitness(childOne), childOne));
        ct++;
        if (ct < count){
            newPopulation.push_back(std::make_pair(findFitness(childTwo), childTwo));
            ct++;
        }
    }
}

//generates two new children based on two randomly selected parents from the population
//calculates the children's fitness scores and then adds them to the new population
//children generated using ordered one point crossover => copies half of parent to child
//then using the other parent, copies the missing nodes from child in order found in 2nd parent
void TSPGenetic::onePtCrossover(float &count){
    int start = 1, middle = 0, parent1 = 0, parent2 = 0;
    int childOneI = 1, childTwoI = 1, ct = 0;
    bool foundOne = false, foundTwo = 0;

    //intialize the children to be the size of the parent vector path
    std::vector<int> childOne;
    std::vector<int> childTwo;
    for (unsigned long i = 0; i < population[0].second.size(); i++){
        childOne.push_back(0);
        childTwo.push_back(0);
    }

    //will find a random number between 0 and the population size to find random parent
    std::random_device seed;
    std::default_random_engine rando(seed());
    std::uniform_int_distribution<int> getPopRange(0, population.size() - 1);

    //start index is 1 and end is the start plus the size of the chromosome / 2
    middle = (population[0].second.size() / 2) - 1;

    while (ct < count){
        //randomly generate the parent indexes from the population used for crossover
        parent1 = getPopRange(rando);
        parent2 = getPopRange(rando);
        childOneI = 1, childTwoI = 1;

        //copy the first half of the parent to the child (p1 => c1)
        for (int i = start; i <= middle; i++){
            childOne[childOneI++] = population[parent1].second[i];
            childTwo[childTwoI++] = population[parent2].second[i];
        }

        //copy the rest of the nodes not in the child to the opposite parent (p1 => c2)
        for (unsigned long i = start; i < population[0].second.size() - 1; i++){
            foundOne = false, foundTwo = false;
            for (int m = start; m <= middle; m++){
                if (population[parent1].second[i] == childTwo[m])
                    foundOne = true;
                if (population[parent2].second[i] == childOne[m])
                    foundTwo = true;
            }
            if (!foundOne)
                childTwo[childTwoI++] = population[parent1].second[i];
            if (!foundTwo)
                childOne[childOneI++] = population[parent2].second[i];
        }

        //calculate the fitness for the children, make pair, and add to new population and
        //check to see if the newPopulation is going to be larger than the population
        newPopulation.push_back(std::make_pair(findFitness(childOne), childOne));
        ct++;
        if (ct < count){
            newPopulation.push_back(std::make_pair(findFitness(childTwo), childTwo));
            ct++;
        }
    }
}

//mutation method that picks (population.size() * percent of population to mutate)
//will swap two random elements in that chromosome/solution and will perform the swap
//according to the value of swapMutVal
void TSPGenetic::swapMutate(){
    int first = 0, second = 0, temp = 0, randomI = 0;
    int numToMutate = population.size() * mutationPercentage;
    std::random_device seed;
    std::default_random_engine rando(seed());
    std::uniform_real_distribution<float> getDistri(0, population.size());
    std::uniform_int_distribution<int> getRange(1, population[0].second.size() - 2);
    while(numToMutate > 0){
        randomI = getDistri(rando);
        for (int s = 0; s < swapMutVal; s++){
                first = getRange(rando);
                second = getRange(rando);
                temp = newPopulation[randomI].second[first];
                newPopulation[randomI].second[first] = newPopulation[randomI].second[second];
                newPopulation[randomI].second[second] = temp;
        }
        numToMutate--;
    }
}

//calls the selection method that corresponds to the
//selectionType value. Accepts a reference float thats
//passed to the selection method
void TSPGenetic::selection(float &count){
    //if selectionType = 0, then run roulette selection
    if (selectionType == 0){
        //std::cout << "++++++ Roulette Selection ++++++" << std::endl;
        rouletteSelection(count);
    }
    //if selectionType = 1, then run elite selection
    else if (selectionType == 1){
        //std::cout << "++++++ Elite Selection ++++++" << std::endl;
        eliteSelection(count);
    }
}

//calls the crossover method that corresponds to the
//crossoverType value. Accepts a reference float thats
//passed to the crossover method
void TSPGenetic::crossover(float &count){
    //if crossover type = 2, then run multiple point crossover
    if (crossoverType == 2){
        //std::cout << "++++++ Multi Point Crossover ++++++" << std::endl;
        multiPtCrossover(count);
    }
    //if crossover type = 3, then run one point crossover
    else if (crossoverType == 3){
        //std::cout << "++++++ One Point Crossover ++++++" << std::endl;
        onePtCrossover(count);
    }
}

//calls the mutation function depending on what the mutateType was
//originally set to
void TSPGenetic::mutate(){
    //if mutateType = 4, then run the swap mutation method
    if (mutateType == 4){
        //std::cout << "++++++ Swap Mutation ++++++" << std::endl;
        swapMutate();
    }
}

//finds the fitness of a chromosome (aka finds the distance of a
//given path) returns a float value of distance and accepts a reference
//to a vector of integers
float TSPGenetic::findFitness(std::vector<int> &path){
    float dist = 0;
    for (unsigned int i = 0; i < path.size() - 1; i++)
        dist += nodeData.costGraph[path[i]][path[i + 1]];
    return dist;
}

//will find the best path (the one that has the best fitness value)
//if a new generation finds a better path, then bestPath is updated
void TSPGenetic::findBestPath(std::chrono::high_resolution_clock::time_point &start,std::chrono::high_resolution_clock::time_point &end){
    //initializes the temp best path to the first in the population and then
    //compares to the rest of the population
    std::pair<float, std::vector<int>> tempBest = population[0];;

    for (unsigned long i = 1; i < population.size(); i++){
        if (population[i].first < tempBest.first)
            tempBest = population[i];
    }

    if (tempBest.first < bestPath.first){
        bestPath = tempBest;
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(end-start);
        std::cout << "\nTiming :: \t" << time.count() << std::endl;
        for (unsigned long i = 0; i < bestPath.second.size(); i++){
                std::cout << bestPath.second[i] + 1 << " => ";
            }
            std::cout << "  Dist:: " << bestPath.first << std::endl;
    }
}

//prints out the population vector of type pair
void TSPGenetic::printPopulation(){
    for (unsigned long i = 0; i < population.size(); i++){
        for (unsigned long c = 0; c < population[i].second.size(); c++){
            std::cout << population[i].second[c] << " => ";
        }
        std::cout << "  Dist:: " << population[i].first << "  " << i << std::endl;
    }
}
