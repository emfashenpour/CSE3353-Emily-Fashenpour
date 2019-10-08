#include "searchalgorithm.h"
#include "search.h"
#include <vector>
#include <stack>
#include <queue>
#include <iostream>

//constructor
SearchAlgorithm::SearchAlgorithm(){
    nodesVisited = 0;
}

//used to pass graph in from the Search class
void SearchAlgorithm::setGraph(Graph *&stor){
    gStore = stor;
}

//returns the path found
std::vector<Node>& SearchAlgorithm::getPath(){
    return path;
}

//returns the number of nodes that were visited in the graph before the
//final path was found
int SearchAlgorithm::getNodesVisited(){
    return nodesVisited;
}

//used with BFS to backtrack over the path that was originally found
//needed otherwise the final path has connections that dont exist in
//the graph
void SearchAlgorithm::findPath(std::vector<Node> &path){
    std::vector<Node> newPath;
    int i1 = path.size() - 1, i2 = path.size() - 2;
    newPath.push_back(path[path.size() - 1]);
    while(i2 != 0){
        if (gStore->getNode(path[i1].id - 1).isConnect(path[i2].id)){
            newPath.push_back(path[i2]);
            i1 = i2;
            i2--;
        }
        else{
            i2--;
        }
    }
    newPath.push_back(path[0]);
    std::reverse(newPath.begin(), newPath.end());
    path = newPath;
}

//iterative DFS, takes a start and destination int
std::vector<Node>& SearchAlgorithm::iterDFS(int start, int dest){
    nodesVisited = 0;
    path.clear();
    Node trackNode;
    std::vector<bool> visit(gStore->getSize(), false);
    std::vector<Connect> connections;
    std::stack<Node> stack;

    stack.push(gStore->getNode(start - 1));

    while (!stack.empty()){
        trackNode = stack.top();

        path.push_back(stack.top());
        visit[stack.top().id - 1] = true;
        nodesVisited++;

        stack.pop();

        if (trackNode.id == dest){
            return path;
        }

        connections = gStore->getNode(trackNode.id - 1).con;

        for (int i = connections.size() - 1; i >= 0; i--){
            if(connections[i].id != -1){
                if (!(visit[connections[i].id -1]))
                    stack.push(gStore->getNode(connections[i].id - 1));
            }
        }
    }
    return path;

}

//recursive DFS, takes a start and destination int and calls the util function
void SearchAlgorithm::recurDFS(int start, int dest){
    nodesVisited = 0;
    path.clear();
    std::vector<bool> visit(gStore->getSize(), false);

    recurDFSUtil(start, dest, visit, path);
}

//enters the start node and then its first connection recursively
std::vector<Node>& SearchAlgorithm::recurDFSUtil(int start, int dest, std::vector<bool> &visit, std::vector<Node> &path){
    std::vector<Connect> connections;
    visit[start - 1] = true;
    nodesVisited++;

    path.push_back(gStore->getNode(start - 1));

    if (start == dest){
        return path;
    }
    connections = gStore->getNode(start - 1).con;

    for (int i = 0; i < connections.size(); i++){
        if (connections[i].id != -1)
            if (visit[connections[i].id - 1] == false)
                return recurDFSUtil(connections[i].id, dest, visit, path);
    }
    return path;

}

//iterative BFS, accepts a start and destination node int
std::vector<Node>& SearchAlgorithm::iterBFS(int start, int dest){
    path.clear();
    Node trackNode;
    std::vector<bool> visit(gStore->getSize(), false);
    std::vector<Connect> connections;
    std::queue<Node> queue;

    queue.push(gStore->getNode(start - 1));
    //path.push_back(queue.front());

    while (!queue.empty()){
        trackNode = queue.front();
        path.push_back(trackNode);

        if (trackNode.id == dest){
            nodesVisited = path.size();
            findPath(path);
            return path;
        }

        visit[trackNode.id - 1] = true;

        queue.pop();


        connections = gStore->getNode(trackNode.id - 1).con;

        for (int i = connections.size() - 1; i >= 0 ; i--){
            if(connections[i].id != -1){
                if (!visit[connections[i].id - 1]){
                    queue.push(gStore->getNode(connections[i].id - 1));
                    visit[connections[i].id - 1] = true;
                }
            }
        }
    }
    nodesVisited = path.size();
    findPath(path);
    return path;

}

//recursive BFS, accepts a start and destination int, calls Util
void SearchAlgorithm::recurBFS(int start, int dest){
    path.clear();
    std::vector<bool> visit(gStore->getSize(), false);
    std::queue<Node> queue;

    queue.push(gStore->getNode(start - 1));
    recurBFSUtil(start, dest, visit, path, queue);

    nodesVisited = path.size();
    findPath(path);
}

//enters start node and pushes all the connections from that node and is then called recusively until a
//path is found
std::vector<Node>& SearchAlgorithm::recurBFSUtil(int start, int dest, std::vector<bool> &visit, std::vector<Node> &path, std::queue<Node> &queue){
    Node trackNode;
    std::vector<Connect> connections;

    visit[start - 1] = true;
    trackNode = queue.front();
    path.push_back(trackNode);

    if (start == dest){
        return path;
    }

    connections = gStore->getNode(trackNode.id - 1).con;
    for (int i = 0; i < connections.size(); i++){
        if (connections[i].id != -1){
            if (!(visit[connections[i].id - 1])){
                visit[connections[i].id - 1] = true;
                queue.push(gStore->getNode(connections[i].id - 1));
            }
        }
    }

    queue.pop();
    return recurBFSUtil(queue.front().id, dest, visit, path, queue);

}

//dijsktra algorithm, accepts a start and end int
void SearchAlgorithm::dijkstra(int start, int dest){
    path.clear();
    if (start == dest){
        path.push_back(gStore->getNode(start - 1));
        return;
    }

}
//a star algorithm, accepts a start and end int
void SearchAlgorithm::aStar(int start, int dest){
    path.clear();
    if (start == dest){
        path.push_back(gStore->getNode(start - 1));
        return;
    }
}
