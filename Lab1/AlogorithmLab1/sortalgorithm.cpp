#include "sortalgorithm.h"
#include <iostream>

SortAlgorithm::SortAlgorithm(){}


//bubble sort algorithm to sort a vector of integers
//accepts a reference int vector as a parameter, no return type
void SortAlgorithm::bubbleSort(std::vector<int> &vecSort){
    //boolean variable to help determine when the vector contain sorted values
    bool isSorted = false;
    int temp = 0;

    //'last' variable contains the index of the last sorted variable
    //once a variable is compared, the greatest values are last, meaning
    //the variables after 'last' are sorted
    int last = vecSort.size() - 1;
    while (!isSorted){
        isSorted = true;
        for (int i = 0; i < last; i++){
            if (vecSort[i] > vecSort[i+1]){
                //swap varaibles
                temp = vecSort[i];
                vecSort[i] = vecSort[i+1];
                vecSort[i+1] = temp;
                isSorted = false;
            } //end if
        } //end for
        last--;
    } //end while
}


//insertion sort algorithm to sort a vector of integers
//accepts a reference int vector as a parameter, no return type
void SortAlgorithm::insertionSort(std::vector<int> &vecSort){
    int temp = 0;
    int index = 0;
    for (int i = 1; i < vecSort.size(); i++){
        index = i;
        while (index > 0 && vecSort[index - 1] > vecSort[index]){
            temp = vecSort[index];
            vecSort[index] = vecSort[index - 1];
            vecSort[index - 1] =  temp;
            index --;
        } //end while
    } //end for
}

//function to call mergeSort with int vector, start value, and end
//value function
//accepts a reference int vector as a parameter, no return type
void SortAlgorithm::mergeSort(std::vector<int> &vecSort){
    mergeS(vecSort, 0, vecSort.size()-1);
}


//merge function to merge all the data back into sorted order
//accepts a vector of intergers, a start, middle, and end value of type int
void SortAlgorithm::merge(std::vector<int> &vecSort, int start, int middle, int end){
    //variables to keep track of indexes in the arrays/vector
    int i, j, k;
    int lSize = middle - start + 1;
    int rSize = end - middle;

    //arrays that will serve as temp arrays for the data in vecSort
    int left[lSize], right[rSize];

    //copying data from vecSort into the temp arrays
    for (i = 0; i < lSize; i++)
        left[i] = vecSort[start + i];
    for (j = 0; j < rSize; j++)
        right[j] = vecSort[middle + 1 + j];

    i = 0;   //variable to hold index of left array
    j = 0;   // varable to hold index of right array
    k = start;   //variable to hold index of vecSort

    //merging sorting variables back into vecSort
    while (i < lSize && j < rSize){
        if (left[i] <= right[j]){
            vecSort[k] = left[i];
            i++;
        } //end if
        else{
            vecSort[k] = right[j];
            j++;
        } //end else
        k++;
    } //end while
    //if any data is left in the temp arrays, add back to vecSort
    while (i < lSize){
        vecSort[k] = left[i];
        i++;
        k++;
    } //end while
    while (j < rSize){
        vecSort[k] = right[j];
        j++;
        k++;
    } //end while
}

//mergeSort algoirthm that sorts a vector of integers
//called recursively, accepts a vector of integers, a start and end value, no return type
void SortAlgorithm::mergeS(std::vector<int> &vecSort, int start, int end){
    if (start < end){
        //set middle value to split the vector
        int middle = (end + start) / 2;
        mergeS(vecSort, start, middle);
        mergeS(vecSort, middle + 1, end);
        merge(vecSort, start, middle, end);
    } //end if
}
