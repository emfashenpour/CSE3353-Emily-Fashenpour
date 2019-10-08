#ifndef ADJLIST_H
#define ADJLIST_H
#include "graph.h"
#include <map>
#include "node.h"

//derived class from Graph that will store a map of integers and Nodes
class AdjList: public Graph{
public:
    AdjList();
    void createGraph(char*, char*, char*);
    void printGraph();
    int getSize();
    Node& operator[](int);
    Node& getNode(int);
private:
    std::map<int, Node> aList;
};

#endif // ADJLIST_H
