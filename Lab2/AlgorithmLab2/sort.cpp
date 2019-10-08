#include "sort.h"
#include <iostream>
#include <fstream>

Sort::Sort(){

}

//accepts a char* that will contain a file name of a dataset
//its values will be added to the vector that is to be sorted
void Sort::load(char* file){
    //clears the vector of any values each time a new file is loaded
    currentSet.clear();

    int temp;
    std::ifstream fileRead;

    fileRead.open(file);

    if (!fileRead)
        std::cout << "Problem here." << std::endl;

    //adds all values from the dataset into the currentSet vector
    while (!fileRead.eof()){
        fileRead >> temp;
        currentSet.push_back(temp);
    }

    fileRead.close();
}


//runs the sorts algo on a selected and loaded dataset and tracks timing
//accepts no parameter and has no return type
void Sort::execute(){
    //variable to track the time it takes for each algorithm to run on a dataset
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point end;

    //bubble
    if(currentAlgo == 0){
        sorter.bubbleSort(currentSet);
        end = std::chrono::high_resolution_clock::now();
    }

    //insertion
    else if (currentAlgo == 1){
        sorter.insertionSort(currentSet);
        end = std::chrono::high_resolution_clock::now();
    }

    //merge
    else if (currentAlgo == 2){
        sorter.mergeSort(currentSet);
        end = std::chrono::high_resolution_clock::now();
    }

    //finds the difference between the start and end time and casts to a double
    std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(end-start);

    //time found above added to the timeStat vector
    timeStat.push_back(time.count());
}


//prints the currentSet vector to the screen
//accepts no parameter and has no return type
void Sort::display(){
    for (int i = 0; i < currentSet.size(); i++)
        std::cout << currentSet[i] << std::endl;
}


//depending on the currentAlgo integer, will print out the algo name
//and the times collected for each sorted file. (times kept in the
//timeStat vector of type double
//accepts no parameter and has no return type
void Sort::stats(){
    //prints out the algo name based on currentAlgo int
    if (currentAlgo == 0)
        std::cout << "+++++++ Algorithm:  BubbleSort+++++++ \n" << std::endl;

    if (currentAlgo == 1)
        std::cout << "+++++++ Algorithm:  InsertionSort+++++++ \n" << std::endl;

    if (currentAlgo == 2)
        std::cout << "+++++++ Algorithm:  MergeSort+++++++ \n" << std::endl;

    //prints times from timeStat vector and the size of its corresponding dataset size
    for (int i = 0; i < timeStat.size(); i++){
        std::cout << "DataSet " << i + 1;

        if (i % 4 == 0)
            std::cout << " of 10 values.";
        if (i % 4 == 1)
            std::cout << " of 1000 values.";
        if (i % 4 == 2)
            std::cout << " of 10000 values.";
        if (i % 4 == 3)
            std::cout << " of 100000 values.";

        std::cout << "\tTime:  " << timeStat[i] << std::endl;
    }

    std::cout << "\n\n" << std::endl;
    timeStat.clear();
}


//sets currentAlgo to the selected algorithm integer
//accepts an integer and has no return type
void Sort::select(int sortNum){
    currentAlgo = sortNum;
}


//will write the sorted vector of a given dataset to a file
//accepts a char pointer which will be used as the file that the
//vector gets written to, no return type
void Sort::save(char* filePath){
    std::ofstream write;
    write.open(filePath);

    for (int i = 0; i < currentSet.size(); i++)
        write << currentSet[i] << std::endl;

    write.close();
}


//will be used for future expandability
void Sort::configure(){}
