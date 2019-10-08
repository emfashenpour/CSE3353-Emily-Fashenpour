#include "readfile.h"
#include <cmath>

ReadFile::ReadFile(){}

void ReadFile::readData(){
    std::vector<float> temp;
    std::ifstream file;
    char line[20] ;
    char* split;

    //opening file 'positions.txt'
    file.open("positions.txt");

    //until the end of the file is read, splits up a line by commas and adds to a temp vector
    while (!file.eof()){
        file >> line;
        split = std::strtok(line, ",");
        while (split != NULL){
            temp.push_back(std::stof(split));
            split = std::strtok(NULL, ",");
        }

        //add the node id and it's xyz position(stored as a tuple) to the map of nodes
        nodes.insert(std::make_pair(temp[0] - 1, std::make_tuple(temp[1], temp[2], temp[3])));

        //clear the temp vector so the next line in the file can add to an empty vector
        temp.clear();
    }

    //close the ifstream file
    file.close();
}

//fills the cost graph with the costs (distance) of traveling between
//nodes. uses the distanceFrom function
void ReadFile::fillCostGraph(){
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

//finds the distance between two points by using the distance formula without the square root
float ReadFile::distanceFrom(int first, int second){
    float total = 0;
    total += pow((std::get<0>(nodes[first]) - std::get<0>(nodes[second])), 2);
    total += pow((std::get<1>(nodes[first]) - std::get<1>(nodes[second])), 2);
    total += pow((std::get<2>(nodes[first]) - std::get<2>(nodes[second])), 2);
    return sqrt(total);
    //return total;
}

//prints out the map of nodes -> the id value of the node and its corresponding xyz position
void ReadFile::printNodes(){
    for (unsigned int i = 0; i < nodes.size(); i++){
        std::cout << "ID: " << i + 1 << "\t";
        std::cout << "Position: " << std::get<0>(nodes[i]) << ", " << std::get<1>(nodes[i]) << ", " << std::get<2>(nodes[i]) << std::endl;
    }
}

//prints the values from the cost graph vector of float vectors
void ReadFile::printCostGraph(){
    for (unsigned int i = 0; i < nodes.size(); i++){
        for (unsigned int c = 0; c < nodes.size(); c++){
            std::cout << costGraph[i][c] << " ";
        }
        std::cout << std::endl;
    }
}
