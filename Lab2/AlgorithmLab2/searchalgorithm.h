#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H
#include "graph.h"
#include "adjlist.h"
#include "adjmatrix.h"
#include <list>
#include <queue>

//class that will contain the search algoithms
//==> DFS(iterative and recuresive), BFS(iterative and
//    recuresive), Dijkstra, and aStar(A*)
class SearchAlgorithm{
public:
    SearchAlgorithm();
    void setGraph(Graph*&);
    std::vector<Node>& getPath();
    int getNodesVisited();
    void findPath(std::vector<Node>&);
    std::vector<Node>& iterDFS(int, int);
    void recurDFS(int, int);
    std::vector<Node>& recurDFSUtil(int, int, std::vector<bool>&, std::vector<Node>&);
    std::vector<Node>& iterBFS(int, int);
    void recurBFS(int, int);
    std::vector<Node>& recurBFSUtil(int, int, std::vector<bool>&, std::vector<Node>&, std::queue<Node>&);
    void dijkstra(int, int);
    void aStar(int, int);
private:
    Graph *gStore;
    std::vector<Node> path;
    int nodesVisited;
};

#endif // SEARCHALGORITHM_H
