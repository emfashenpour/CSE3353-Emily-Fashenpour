#include "tspalgorithm.h"
#include <cmath>

//constructor - initializes class variables
TSPAlgorithm::TSPAlgorithm(){
    indexShortest = 0;
    totalPaths = 1;

    nodes = fileData.readData();

    fillCostGraph();
    printCostGraph();
    totalPathsToFind();
}

//Traveling salesman problem - hamaltonian circuit - naive implementation
void TSPAlgorithm::TSPNaive(){
    std::cout << "\n========== Naive Implementation: TSP ==========" << std::endl;
    int startNode = 0;
    int callCount = 0;

    //bool vector visited and float vector to store a path that will be pushed to paths
    std::vector<bool> visited(nodes.size(), false);
    std::vector<float> path;

    //set the starting node index in the vistited vector to truw
    visited[startNode] = true;

    //naive recursive call
    naiveRecur(startNode, 0, visited, path, callCount);

    //finds the shortest path once all permtations are found and prints the results
    findTotalDistance();
    printNaiveShortestPath();

    std::cout << "\nNumber of calls :: \t" << callCount << std::endl;

    return;
}

//naive implentation recursive call function. Takes an int for start node, int index (current node), bool vector for visited
//nodes, a vector of floats for path, and a reference int to track number of times the recursive fucntion is called. Returns a void
void TSPAlgorithm::naiveRecur(int startNode, int index, std::vector<bool> visited, std::vector<float> &path, int &callCount){
    callCount++;

    //adds current node to the path vector and sets that value to true in visited
    path.push_back(index);
    visited[index] = true;

    //if all the nodes are visited, that means a complete path has been found (stop case)
    if (allVisited(visited)){
        //adds the start node to complete the path and pushes the path to the paths vector of float vectors
        path.push_back(startNode);
        paths.push_back(path);

        //deletes the last item in path which is the startNode
        path.pop_back();
        return;
    }
    //if visited is not all visited, then need to keep finding all permatations/paths
    for (unsigned int i = 0; i < visited.size(); i++){
        if (visited[i] == false){
            //checks to see if all possible paths have been found
            if (paths.size() == totalPaths)
                return;

            naiveRecur(startNode, i, visited, path, callCount);

            //by popping off the back, we can delete parts of path
            path.pop_back();
        }
    }
}

//dynamic implementation for the traveling salesman problem
//no return type or paramters, utilizes the dynamRecur function to retrieve the total
//distance traveled and the shortest path traveled
void TSPAlgorithm::TSPDynamic(){

    std::cout << "\n========== Dynamic Implementation: TSP ==========" << std::endl;
    int startNode = 0;
    int callCount = 0;

    //initializes the nodesIds vecotr to have all the nodes in ascending order
    std::vector<int> nodeIds;
    for (unsigned int i = 0; i < nodes.size(); i++){
        nodeIds.push_back(i);
    }

    //sets path of type pair to the dynamRecur fucntion because it returns a type pair
    std::pair<float, std::vector<int>> path = dynamRecur(startNode, 0, 0, nodeIds, callCount);

    //prints the shortest path, total distance traveled and the number of
    //times the recursive function was called
    std::cout << "Shortest Path :: \t" << startNode + 1 << " ";
    for (unsigned int i = path.second.size() - 1; i > 0; i--){
        std::cout << path.second[i] + 1 << " ";
    }
    std::cout << startNode + 1 << std::endl;
    //std::cout << "Total Distance :: \t" << sqrt(path.first) << std::endl;
    std::cout << "Total Distance :: \t" << path.first << std::endl;

    std::cout << "\nNumber of calls :: \t" << callCount << std::endl;
}


//returns type pair of float for the distance and vector of int for the path of nodes for shortest path
//takes a startNode, connect int, index int of connect, a vector of int for nodes, and int reference to track calls made
std::pair<float, std::vector<int>> TSPAlgorithm::dynamRecur(int startNode, int connect, int index, std::vector<int> nodes, int &callCount){
    callCount++;

    //initialze variable to track shortest path and distance
    std::pair<float, std::vector<int>> tempPath;
    std::vector<int> pathVec;
    float dist = MAX;
    float tempDist;

    //erases the node connect by using the index
    nodes.erase(nodes.begin()+index);

    //base case to check to see if the nodes vector only has one item
    if (nodes.size() == 1){
        pathVec.push_back(connect);
        pathVec.push_back(nodes[0]);
        tempPath = std::make_pair(costGraph[connect][nodes[0]] + costGraph[nodes[0]][startNode], pathVec);
        return tempPath;
    }

    //loops through the nodes vector and passes each node to find the shortest path
    for (unsigned int i = 0; i <  nodes.size(); i++){
        tempPath = dynamRecur(startNode, nodes[i], i, nodes, callCount);
        tempDist = costGraph[connect][nodes[i]] + tempPath.first;

        //checks to see if one recursive distance found is less than another
        //if tempDist is less that dist, dist is set to tempDist
        if (tempDist < dist){
            dist = tempDist;
            tempPath.second.push_back(nodes[i]);
            pathVec = tempPath.second;
        }
    }
    return std::make_pair(dist, pathVec);
}

//fills the cost graph with the costs (distance) of traveling between
//nodes. uses the distanceFrom function
void TSPAlgorithm::fillCostGraph(){
    for (unsigned int i = 0; i < nodes.size(); i++){
        costGraph.push_back(std::vector<float>(nodes.size(), 0));
    }
    for (unsigned int i = 0; i < nodes.size(); i++){
        for (unsigned int c = i; c < nodes.size(); c++){
            costGraph[i][c] = distanceFrom(i,c);
            costGraph[c][i] = distanceFrom(i,c);
        }
    }
}

//used in naive approach. Below -> (n-1)!/2
//used because once the number value has been found using the above equation,
//if the number of paths found is equal to this, the paths repeat just backwards
//but the costs/distance is the same so that function calls are needless
void TSPAlgorithm::totalPathsToFind(){
    totalPaths = 1;
    for (int i = nodes.size() - 1; i > 0; i--){
        totalPaths *= i;
    }
    totalPaths /= 2;
}

//returns a boolean if all the nodes have been visited based on the visited vector passed in by reference
bool TSPAlgorithm::allVisited(std::vector<bool> &visit){
    for (unsigned int i = 0; i < visit.size(); i++){
        if (visit[i] == false)
            return false;
    }
    return true;
}

//finds the distance between two points by using the distance formula without the square root
float TSPAlgorithm::distanceFrom(int first, int second){
    float total = 0;
    total += pow((std::get<0>(nodes[first]) - std::get<0>(nodes[second])), 2);
    total += pow((std::get<1>(nodes[first]) - std::get<1>(nodes[second])), 2);
    total += pow((std::get<2>(nodes[first]) - std::get<2>(nodes[second])), 2);
    return sqrt(total);
}

//will find the total distance of each path and add the total path distance
//to the end of the path vector in the vector of vector paths
//also sets the variable indexShortest to the lowest cost/distance path
void TSPAlgorithm::findTotalDistance(){
    float temp;
    indexShortest = 0;
    for (unsigned int i = 0; i < paths.size(); i++){
        temp = 0;
        for (unsigned int c = 0; c < paths[i].size() - 1; c++){
            //uses costGroph to get the distance value of one node in path to the next node
            temp += distanceFrom(paths[i][c], paths[i][c + 1]);
        }
        //adding the distance of each path to the end of their respective vector
        paths[i].push_back(temp);
        //compare here to set lowest index
        if (paths[i][paths[i].size() -1] < paths[indexShortest][paths[indexShortest].size() -1])
            indexShortest = i;
    }
}

//prints out the map of nodes -> the id value of the node and its corresponding xyz position
void TSPAlgorithm::printNodes(){
    for (unsigned int i = 0; i < nodes.size(); i++){
        std::cout << "ID: " << i + 1 << "\t";
        std::cout << "Position: " << std::get<0>(nodes[i]) << ", " << std::get<1>(nodes[i]) << ", " << std::get<2>(nodes[i]) << std::endl;
    }
}

//prints the values from the cost graph vector of float vectors
void TSPAlgorithm::printCostGraph(){
    for (unsigned int i = 0; i < nodes.size(); i++){
        for (unsigned int c = 0; c < nodes.size(); c++){
            std::cout << costGraph[i][c] << " ";
        }
        std::cout << std::endl;
    }
}

//prints out all the permatations found in the naive approach using the paths vector of float vectors
void TSPAlgorithm::printNaivePaths(){
    for (unsigned int i = 0; i < paths.size(); i++){
        for (unsigned int c = 0; c < paths[i].size(); c++){
            std::cout << paths[i][c] + 1 << " ";
        }
        std::cout << std::endl;
    }
}

//prints the shorest path found from all the naive permatations using the indexShortest variable
void TSPAlgorithm::printNaiveShortestPath(){
    std::cout << "Shortest Path :: \t";
    for (unsigned int i = 0; i < paths[indexShortest].size() - 1; i++){
        std::cout << paths[indexShortest][i] + 1 << " ";
        if (i != paths[indexShortest].size() - 2)
            std::cout << "-> ";
    }
    //the last element in each vector in the vector of floats vectors is the distance element for that path
    std::cout << "\nTotal Distance :: \t" << sqrt(paths[indexShortest][paths[indexShortest].size() - 1]) << std::endl;
}


