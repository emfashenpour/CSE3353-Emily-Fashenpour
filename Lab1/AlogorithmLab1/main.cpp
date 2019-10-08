#include <iostream>
#include <vector>
#include "algorithm.h"
#include "sort.h"
#include "datacreator.h"

int main()
{
    int sizeArr[4] = {10, 1000, 10000, 100000};
    char* fileArr[16] = {"random1.txt", "random2.txt", "random3.txt", "random4.txt",
                         "rever1.txt", "rever2.txt", "rever3.txt", "rever4.txt",
                         "uniq1.txt", "uniq2.txt", "uniq3.txt", "uniq4.txt",
                         "rand301.txt", "rand302.txt", "rand303.txt", "rand304.txt"};

    enum algo{BUBBLE, INSERTION, MERGE, LAST};

    //create all the files to be sorted
    DataCreator create;
    create.createFiles(fileArr, sizeArr);


    //Algorithm object declaration
    Algorithm *sort = new Sort();


    //loop through all the algorithms and for each algo, run all 16
    //files in the fileArr array
    for (int al = BUBBLE; al < LAST; al++){
        sort->select(al);
        for (int i = 0; i < 16; i++){
            sort->load(fileArr[i]);
            sort->execute();


            /*
             * Change fileArr[1] to any file named from the fileArr array
             * and al to equal any of the sort algorithms (BUBBLE, INSERTION, MERGE)
             * to save that file's sorted solution to the sorted.txt file
             *
             *
             *
            if (fileArr[i] == fileArr[1] && al == BUBBLE){
                sort->save("sorted.txt");
            }
            */

        }

        //prints the times for each algorithm and files of differing sizes
        sort->stats();
    }

    return 0;
}
