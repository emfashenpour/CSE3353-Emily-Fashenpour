#ifndef DATACREATOR_H
#define DATACREATOR_H

//class that will write the data files to be sorted
//will have 4 data files of differing sizes for each
//of the different function => random, reversed sorted order,
//20% unique values, and 30% randomized values
class DataCreator
{
public:
    DataCreator();
    void random(int, char*);
    void reversed(int, char*);
    void unique20(int, char*);
    void random30(int, char*);
    void createFiles(char**, int*);
};

#endif // DATACREATOR_H
