#ifndef NODE_H
#define NODE_H
#include "connect.h"
#include <vector>

//Object class that will store the id, the position,
//and a vector of its connections (of Connect objects)
class Node{
public:
    Node();
    Node(int);
    Node(int, Connect, std::tuple<float,float, float>);
    void pushConnection(int);
    void pushWeight(int, float);
    void setPosition(std::tuple<float, float, float>);
    bool isConnect(int);
    float getCost(int);
    void print();

    int id;
    std::vector<Connect> con;
    std::tuple<float,float,float> position;
};

#endif // NODE_H
