#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"

//will serve as the parent class to
//AdjMatrix and AdjList
class Graph{
public:
    virtual void createGraph(char*, char*, char*) = 0;
    virtual void printGraph() = 0;
    virtual int getSize() = 0;
    virtual Node& operator[](int) = 0;
    virtual Node& getNode(int) = 0;
};

#endif // GRAPH_H
