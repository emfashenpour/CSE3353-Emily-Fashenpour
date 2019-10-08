#ifndef ALGOFACTORY_H
#define ALGOFACTORY_H
#include "absalgorithm.h"

//algoFactory will return a AbsAlgorithm pointer
//depending on which algorithm the user selected
//utilizes the factory design pattern
class AlgoFactory
{
public:
    AlgoFactory();
    static AbsAlgorithm* create(int);
};

#endif // ALGOFACTORY_H
