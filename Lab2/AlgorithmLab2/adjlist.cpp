#include "adjlist.h"
#include <vector>
#include <fstream>
#include <iostream>

AdjList::AdjList(){}

//createGraph fucntion accepts three char pointers for the files that
//will be read into to make the map of ints and nodes
void AdjList::createGraph(char* gra, char* pos, char* wei){
    std::vector<float> contain;
    char line[20];
    char* split;

    //opens the graph file
    std::ifstream file;
    file.open(gra);

    //splits up each line by ',' delimiter and then casts
    //each value found to a float to store in the float vector
    while(!file.eof()){
        file >> line;
        split = std::strtok(line, ",");
        while (split != NULL){
            contain.push_back(std::stof(split));
            split = std::strtok(NULL, ",");
        }

        //creates the pair for map using the id of the node
        aList.insert(std::make_pair(contain[0] - 1, Node(contain[0])));

        //adds the connections from the node above to the other nodes
        for (unsigned int i = 1; i < contain.size(); i++){
            aList[contain[0] - 1].pushConnection(contain[i]);
        }
        //clears the vector so it can store the info from the next
        //line in the file
        contain.clear();
    }

    file.close();

    //opens the position file
    file.open(pos);

    //z will hold zero in case there is only an xy-plane given for position
    float z = 0;
    while (!file.eof()){
        file >> line;
        split = std::strtok(line, ",");
        while (split != NULL){
            contain.push_back(std::stof(split));
            split = std::strtok(NULL, ",");
        }

        //checks to see if there is an xy- or xyz-plane for position
        if (contain.size() == 4)
            z = contain[3];

        //creates the tuple for position and adds to corresponding node
        auto position = std::make_tuple(contain[1], contain[2], z);
        aList[contain[0] - 1].setPosition(position);

        //clears the vector so it can store the info from the next
        //line in the file
        contain.clear();
    }

    file.close();

    //opens the weights file
    file.open(wei);

    while (!file.eof()){
        file >> line;
        split = std::strtok(line, ",");
        while (split != NULL){
            contain.push_back(std::stof(split));
            split = std::strtok(NULL, ",");
        }

        //adds the weight of each connection to the corresponding Connect
        //object in the Node object
        aList[contain[0] - 1].pushWeight(contain[1], contain[2]);

        //clears the vector so it can store the info from the next
        //line in the file
        contain.clear();
    }

    file.close();
}

//returns the size of the map
int AdjList::getSize(){
    return aList.size();
}

//prints the map of nodes
void AdjList::printGraph(){
    for (unsigned int i = 0; i < aList.size(); i++){
        std::cout << "++++++" << std::endl;
        aList[i].print();
    }
}

//overloaded bracket operator
Node& AdjList::operator[](int x){
    return aList[x];
}

//returns the node at the index passed in from the map
Node& AdjList::getNode(int x){
    return aList[x];
}
