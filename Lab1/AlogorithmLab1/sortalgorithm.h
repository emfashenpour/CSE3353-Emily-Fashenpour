#ifndef SORTALGORITHM_H
#define SORTALGORITHM_H
#include <vector>

//class will contain functions
//==> bubble, insertion, and merge sort algoithms
class SortAlgorithm{
public:
    SortAlgorithm();
    void bubbleSort(std::vector<int>&);
    void insertionSort(std::vector<int>&);
    void mergeSort(std::vector<int>&);
    void merge(std::vector<int>&, int, int, int);
    void mergeS(std::vector<int>&, int, int);
};

#endif // SORTALGORITHM_H
