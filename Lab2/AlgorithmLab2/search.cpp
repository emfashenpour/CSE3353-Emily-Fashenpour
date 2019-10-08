#include "search.h"
#include <iostream>
#include <fstream>
#include "math.h"

//constructor
Search::Search(){
    currentAlgo = 0;
    currentStore = 0;
}

//accepts a char pointer and sets the currentStore int for tracking if
//the graph is a matrix or a list. Then loads all the data from the files
//resets the path vector, and passes the graph object as a reference to
//the searchAlgo class in order to do searches on it
void Search::load(char *st){
    if (st == "m"){
        currentStore = 0;
        gStore = new AdjMatrix();
    }
    else{
        currentStore = 1;
        gStore = new AdjList();
    }

    gStore->createGraph("graph.txt", "positions.txt", "weights.txt");
    path.clear();
    searcher.setGraph(gStore);
}

void Search::execute(){

}

//will execute the corresponding algorithm based on the currentAlgo variable
void Search::execute(int start, int end){
    path.clear();
    //the search algo methods will need to return path from start to dest

    //will also need to add the timing elements to the vector of doubles
    std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point timeEnd;

    //values 0 - 5 correspond to the SearchAlgo enum
    if (currentAlgo == 0){
        searcher.iterDFS(start, end);
        timeEnd = std::chrono::high_resolution_clock::now();
    }
    else if(currentAlgo == 1){
        searcher.recurDFS(start, end);
        timeEnd = std::chrono::high_resolution_clock::now();
    }
    else if(currentAlgo == 2){
        searcher.iterBFS(start, end);
        timeEnd = std::chrono::high_resolution_clock::now();
    }
    else if(currentAlgo == 3){
        searcher.recurBFS(start, end);
        timeEnd = std::chrono::high_resolution_clock::now();
    }
    else if(currentAlgo == 4){
        searcher.dijkstra(start, end);
        timeEnd = std::chrono::high_resolution_clock::now();
    }
    else if(currentAlgo == 5){
        searcher.aStar(start, end);
        timeEnd = std::chrono::high_resolution_clock::now();
    }
    std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(timeEnd-timeStart);

    //gets path from the searchAlgo class
    path = searcher.getPath();
    if (path.size() != 0){
        timeStat.push_back(time.count());
        numNodesPath.push_back(path.size());
        nodesVisit = searcher.getNodesVisited();
        nodesVisited.push_back(nodesVisit);
        costs.push_back(getCost());
        distances.push_back(getDistance());
    }
    //case for if there is no path found from one of the search algos
    else{
        cost = 0;
        distance = 0;
        nodesVisit = 0;
        timeStat.push_back(0);
        numNodesPath.push_back(0);
        nodesVisited.push_back(0);
        costs.push_back(0);
        distances.push_back(0);
    }
}

//will need to display the path found from the start to dest
void Search::display(){
    std::cout << "Algorithm ::  ";
    if (currentAlgo == 0)
        std::cout << "Iterative DFS";
    else if (currentAlgo == 1)
        std::cout << "Recursive DFS";
    else if (currentAlgo == 2)
        std::cout << "Iterative BFS";
    else if (currentAlgo == 3)
        std::cout << "Recursive BFS";
    else if (currentAlgo == 4)
        std::cout << "Dijkstra";
    else if (currentAlgo == 5)
        std::cout << "A*";

    if (currentStore == 0)
        std::cout << "  on  Adjacency Matrix" << std::endl;
    else if (currentStore == 1)
            std::cout << "  on  Adjacency List" << std::endl;

    std::cout << "Path ::  ";
    for (int i = 0; i < path.size(); i++){
        std::cout << path[i].id;
        if (i != path.size() - 1)
            std::cout << " => ";
    }
    std::cout << "\nNum Nodes in Path ::  " << path.size() << std::endl;
    std::cout << "Num Nodes Visited ::  " << nodesVisit << std::endl;
    std::cout << "Cost of Path ::  " << cost << std::endl;
    std::cout << "Distance of Path ::  " << distance << std::endl;
    std::cout << "\n" << std::endl;
}

//will print all timing and corresponding algo types
//for each start to destination path timing
void Search::stats(){
    if (currentStore == 0)
        save("matrixResults.txt");
    if (currentStore == 1)
        save("listResult.txt");
}

//sets the currentAlgo variable to the integer passed as a parameter
void Search::select(int i){
    currentAlgo = i;
}

//will all all timing and corresponding algo types to a file
//for each start to destination path timing
void Search::save(char *file){
    int index = 0;
    std::ofstream write;
    write.open(file);

    if (currentStore == 0)
        write << "matrixResults" << std::endl;
    if (currentStore == 1)
        write << "listResult" << std::endl;

    while(index != timeStat.size()){
        if (index % (timeStat.size() / 6) == 0)
            write << "\n\nTime" << std::endl;
        write << timeStat[index] << std::endl;
        index++;
    }
    index = 0;
    while(index != numNodesPath.size()){
        if (index % (numNodesPath.size() / 6) == 0)
            write << "\n\nNum Nodes" << std::endl;
        write << numNodesPath[index] << std::endl;
        index++;
    }
    index = 0;
    while(index != nodesVisited.size()){
        if (index % (nodesVisited.size() / 6) == 0)
            write << "\n\nNum Visited" << std::endl;
        write << nodesVisited[index] << std::endl;
        index++;
    }
    index = 0;
    while(index != costs.size()){
        if (index % (costs.size() / 6) == 0)
            write << "\n\nCosts" << std::endl;
        write << costs[index] << std::endl;
        index++;
    }
    index = 0;
    while(index != distances.size()){
        if (index % (distances.size() / 6) == 0)
            write << "\nDistances" << std::endl;
        write << distances[index] << std::endl;
        index++;
    }

    write.close();
    std::cout << "\nResults printed to the file\n" << std::endl;
}

//will be used for future expandability
void Search::configure(){

}

//used to find the size of the adjMatrix or AdjList
int Search::storeSize(){
    return gStore->getSize();
}

//calculates the total cost of a path
float Search::getCost(){
    float costF = 0;
    for (int i = 0; i < path.size()-1; i++){
        costF += path[i].getCost(path[i + 1].id);
    }
    cost = costF;
    return costF;
}

//calculates the distance of the total path traveled
float Search::getDistance(){
    float distanceF = 0;
    for (int i = 0; i < path.size()-1; i++){
        distanceF += distanceFunc(gStore->getNode(path[i].id - 1).position, gStore->getNode(path[i + 1].id - 1).position);
    }
    distance = distanceF;
    return distance;
}

//fucntion used to calculate the distance of the nodes in the path
float Search::distanceFunc(std::tuple<float, float, float> &pos1, std::tuple<float, float, float> &pos2){
    float v1 = pow((std::get<0>(pos1) - std::get<0>(pos2)), 2);
    float v2 = pow((std::get<1>(pos1) - std::get<1>(pos2)), 2);
    float v3 = pow((std::get<2>(pos1) - std::get<2>(pos2)), 2);
    return v1 + v2 + v3;
}
