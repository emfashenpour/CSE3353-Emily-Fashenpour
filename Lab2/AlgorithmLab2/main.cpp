#include <iostream>
#include "algorithm.h"
#include "search.h"
#include "searchalgorithm.h"
#include "node.h"
#include "connect.h"
#include "adjlist.h"
#include "adjmatrix.h"
#include <map>
#include <fstream>
#include <sstream>
#include <time.h>


int main(int argc, char* argv[]){
    //enum to track algorithm type and graph types
    enum storageType{ADJLIST = 0, ADJMATRIX};
    enum SearchAlgo{ITERDFS = 0, RECURDFS, ITERBFS, RECURFBS, DIJKSTRA, ASTAR, LAST};

    //initializing the two different graph types
    Search *searchMat = new Search();
    Search *searchList = new Search();

    //loads in all the files and stores them in the adjMatrix and then
    //the adjList
    searchMat->load("m");
    searchList->load("l");

    if (argc > 1){
        //when there is something in the command line, find the source to
        //destination of the two arguments passed in
        std::cout << "Something in command line.\n" << std::endl;
        int start = atoi(argv[1]);
        int dest = atoi(argv[2]);

        for (int i = ITERDFS; i < LAST; i++){
            //selects the algo, finds the path, and prints the path and all it's data
            searchList->select(i);
            searchList->execute(start, dest);
            searchList->display();
            searchMat->select(i);
            searchMat->execute(start, dest);
            searchMat->display();
        }

        searchMat->stats();
        searchList->stats();
    }
    else{
        //if there is nothing in the command line, then run all the tests to collect data
        std::cout << "Nothing in command line.\n" << std::endl;

        int random = 0;
        std::vector<int> points;
        //srand(time(NULL));


        //adding to a vector of 100 source and destinations to test
        for (int i = 0; i < 200; i++){
            random = rand() % (searchMat->storeSize()) + 1;
            points.push_back(random);
        }
        std::cout << points.size() << std::endl;

        //source => destination
        for (int c = ITERDFS; c < LAST; c++){
            searchMat->select(c);
            searchList->select(c);
            std::cout << "here" << std::endl;
            for (int z = 0; z < 100 - 1; z++){
                searchMat->execute(points[z],points[z+1]);
                searchList->execute(points[z],points[z+1]);
            }

        }

        //destination => source
        for (int c = ITERDFS; c < LAST; c++){
            searchMat->select(c);
            searchList->select(c);
            for (int z = 0; z < 100; z++){
                searchMat->execute(points[z+1],points[z]);
                searchList->execute(points[z+1],points[z]);
            }

        }
        //write all data to the file
        searchMat->stats();
        searchList->stats();
    }

    return 0;
}
