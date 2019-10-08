#ifndef SEARCH_H
#define SEARCH_H
#include "algorithm.h"
#include "searchalgorithm.h"
#include "graph.h"
#include "adjlist.h"
#include "adjmatrix.h"
#include <vector>
#include <chrono>

//derived class from Algorithm
//will implement all the methods from Algorithm
class Search: public Algorithm{
public:
    Search();
    void load(char*);
    void execute();
    void execute(int, int);
    void display();
    void stats();
    void select(int);
    void save(char*);
    void configure();
    int storeSize();
    float getCost();
    float getDistance();
    float distanceFunc(std::tuple<float, float, float>&, std::tuple<float, float, float>&);
private:
    SearchAlgorithm searcher;
    Graph *gStore;
    std::vector<Node> path;
    int currentAlgo;
    int currentStore;

    //
    float cost;
    float distance;
    int nodesVisit;


    //containers for storing the algorithm data
    std::vector<double> timeStat;
    std::vector<int> numNodesPath;
    std::vector<int> nodesVisited;
    std::vector<float> costs;
    std::vector<int> distances;
};

#endif // SEARCH_H
