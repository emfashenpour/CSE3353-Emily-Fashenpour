#include "adjmatrix.h"
#include <vector>
#include <fstream>
#include <iostream>

//constructor initializes the vectors
AdjMatrix::AdjMatrix(){
    findMax(); //finds the highest number node and initializes the aMatrix vector to that number minus one
}

//createGraph function accepts three char pointers for the file
//that will be read into to add Nodes to the vector
void AdjMatrix::createGraph(char* gra, char* pos, char* wei){
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

        //adds the connections to each node
        for (unsigned int i = 1; i < contain.size(); i++){
            aMatrix[contain[0] - 1].con[contain[i] - 1] = contain[i];
        }

        //clears the vector so it can store the info from the next
        //line in the file
        contain.clear();
    }


    file.close();

    //opens the positions file
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
        aMatrix[contain[0] - 1].setPosition(position);

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
        aMatrix[contain[0] - 1].pushWeight(contain[1], contain[2]);

        //clears the vector so it can store the info from the next
        //line in the file
        contain.clear();
    }

    file.close();

}

//prints the vector of nodes
void AdjMatrix::printGraph(){
    for (unsigned int i = 0; i < aMatrix.size(); i++){
            std::cout << "++++++" << std::endl;
            aMatrix[i].print();
    }
}

//returns the size of the vector
int AdjMatrix::getSize(){
    return aMatrix.size();
}

//overloaded bracket operator
Node& AdjMatrix::operator[](int x){
    return aMatrix[x];
}

//returns the node at the index passed in by the parameter
Node& AdjMatrix::getNode(int x){
    return aMatrix[x];
}

//finds the highest node value in the graph file and initializes
//the vector of Nodes and the vector in the Nodes to max size
void AdjMatrix::findMax(){
    char line[20];
    char* split;

    float max = 0, val = 0;

    //finds the highest number node in the graph.txt file
    std::ifstream file;
    file.open("graph.txt");
    while(!file.eof()){
        file >> line;
        split = std::strtok(line, ",");
        while (split != NULL){
            val = std::stof(split);
            if (val > max){
                max = val;
            }
            split = std::strtok(NULL, ",");
        }
    }

    for (int i = 0; i < max; i++){
        //initializes the vector to contain Nodes with an id of -1
        //-1 will be used to indicate that there are no connections at
        //that point in the matrix
        aMatrix.push_back(Node(i + 1));
        for (unsigned int c = 0; c < max; c++){
            aMatrix[i].con.push_back(Connect(-1));
        }
    }
}
