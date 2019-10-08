#ifndef ADJMATRIX_H
#define ADJMATRIX_H
#include "graph.h"
#include "node.h"

//derived class from Graph that will store a vector of Nodes
class AdjMatrix: public Graph{
public:
    AdjMatrix();
    void createGraph(char*, char*, char*);
    void printGraph();
    int getSize();
    Node& operator[](int);
    Node& getNode(int);
    void findMax();
private:
    std::vector<Node> aMatrix;
};

#endif // ADJMATRIX_H
