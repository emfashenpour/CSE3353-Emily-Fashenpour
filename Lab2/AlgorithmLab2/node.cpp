#include "node.h"
#include <iostream>

//constructor
Node::Node(){
    id = 0;
}

//constructor
Node::Node(int i){
    id = i;
}

//constructor
Node::Node(int i, Connect c, std::tuple<float,float,float> p){
    id = i;
    con.push_back(c);
    position = p;
}

//adds a new Connect object to the vector of connect objects called connections
void Node::pushConnection(int i){
    con.push_back(Connect(i));
}

//adds the weight of the connect object of the id passed in by num
void Node::pushWeight(int num, float d){
    for (unsigned int i = 0; i < con.size(); i++){
        if (con[i].id == num){
            con[i].setWeight(d);
        }
    }
}

//sets the position varibale to the tuple passed as a parameter
void Node::setPosition(std::tuple<float, float, float> pos){
    position = pos;
}

//returns a boolean if there is a connection found
//checks to see if the id of the parameter matches
//any of the ids in the connections vector
bool Node::isConnect(int id2){
    for (int i = 0; i < con.size(); i++){
        if (id2 == con[i].id)
            return true;
    }
    return false;
}

//returns the weight of the connection between node id and the id
//of the parameter. If none found, returns 0
float Node::getCost(int id1){
    for (int i = 0; i < con.size(); i++){
        if (con[i].id == id1)
            return con[i].weight;
    }
    return 0;
}

//prints the node object ta a certain format
void Node::print(){
    std::cout << id << " " << std::endl;
    std:: cout << std::get<0>(position) << ", " << std::get<1>(position) << ", " << std::get<2>(position) << std::endl;
    for (int i = 0; i < con.size(); i++){
        std::cout << con[i].id << " (" << con[i].weight << ")\n";
    }
}
