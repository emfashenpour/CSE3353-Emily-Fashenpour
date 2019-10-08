#include "readfile.h"

ReadFile::ReadFile(){}

std::map<int, std::tuple<float, float, float>>& ReadFile::readData(){
    std::vector<float> temp;
    std::ifstream file;
    char line[20] ;
    char* split;

    //opening file 'positions.txt'
    file.open("positions.txt");

    //until the end of the file is read, splits up a line by commas and adds to a temp vector
    while (!file.eof()){
        file >> line;
        split = std::strtok(line, ",");
        while (split != NULL){
            temp.push_back(std::stof(split));
            split = std::strtok(NULL, ",");
        }

        //add the node id and it's xyz position(stored as a tuple) to the map of nodes
        nodes.insert(std::make_pair(temp[0] - 1, std::make_tuple(temp[1], temp[2], temp[3])));

        //clear the temp vector so the next line in the file can add to an empty vector
        temp.clear();
    }

    //close the ifstream file
    file.close();
    return nodes;
}
