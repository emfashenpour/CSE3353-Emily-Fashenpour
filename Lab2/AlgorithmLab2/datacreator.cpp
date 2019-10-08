#include "datacreator.h"
#include <fstream>

DataCreator::DataCreator(){}

//will create a file of randomly generated numbers between zero
//and the size of the file
//accepts an integer for size and a character pointer for fileName
void DataCreator::random(int size, char* file){
    int random;
    std::ofstream myFile;
    srand(time(NULL));

    myFile.open(file);

    for (int i = 0; i < size; i++){
        //assigning a random number from 0 to file size
        random = rand() % size;
        myFile << random << std::endl;
    }

    myFile.close();
}


//will create a file of integers sorted in reverse
//accepts an integer for size of the file and a character
//pointer for the fileName, no return type
void DataCreator::reversed(int size, char* file){
    std::ofstream myFile;

    myFile.open(file);

    //writes a number starting at size to zero to the file
    for (int i = size; i > 0; i--)
        myFile << i << std::endl;

    myFile.close();
}


//will generate a file of a specified size
//will randomly write a number between 1 and 5 (so in the end
//there are only 20% unique values. When there size is 10, there are
//only two each number from 1 to 5, etc)
//accepts an integer for size of the file and a character
//pointer for the fileName, no return type
void DataCreator::unique20(int size, char* file){
    int random;
    int arrVal[5];
    std::ofstream myFile;
    srand(time(NULL));

    myFile.open(file);

    //adds five random values to an array of integers
    for (int i = 0; i < 5; i++){
        random = (rand() % size) + 1;
        arrVal[i] = random;
    }

    //adds each value from the arrVal array size*.2 (20%) times
    for (int s = 0; s < (size*.2); s++){
        for (int i = 0; i < 5; i++){
            myFile << arrVal[i] << std::endl;
        }
    }

    myFile.close();
}


//will generate a file where 70% of the numbers are in sorted order
//and 30% are random
//accepts an integer for size of the file and a character
//pointer for the fileName, no return type
void DataCreator::random30(int size, char* file){
    int random, num = 0;
    std::ofstream myFile;
    srand(time(NULL));

    myFile.open(file);

    //writes 10% of sorted numbers
    for (int i = 0; i < (size*(.1)); i++)
        myFile << num++ << std::endl;

    //writes 30% of random unsorted values
    for (int i = 0; i < (size*(.3)); i++){
        //generates random between 0 and size
        random = rand() % size;
        myFile << random << std::endl;
    }

    //writes other 60% of sorted numbers
    for (int i = 0; i < (size*(.6)); i++)
        myFile << num++ << std::endl;

    myFile.close();
}

void DataCreator::createFiles(char** fileNames, int* sizes){
    //int variable to keep track of the fileName index
    int fId = 0;

    //create the four files of different sizes of random
    for (int i = 0; i < 4; i++){
        random(sizes[i], fileNames[fId]);
        fId++;
    }

    //create the four files of different sizes of reversed sorted order
    for (int i = 0; i < 4; i++){
        reversed(sizes[i], fileNames[fId]);
        fId++;
    }

    //create the four files of different sizes for unique 20% values
    for (int i = 0; i < 4; i++){
        unique20(sizes[i], fileNames[fId]);
        fId++;
    }

    //create the four files of different sizes for 30% random not sorted values
    for (int i = 0; i < 4; i++){
        random30(sizes[i], fileNames[fId]);
        fId++;
    }
}
