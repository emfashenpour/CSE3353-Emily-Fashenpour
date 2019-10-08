#ifndef ABSALGORITHM_H
#define ABSALGORITHM_H

//parent class for all algorithms'
//utilizes the strategy design pattern
class AbsAlgorithm{
public:
    virtual AbsAlgorithm* select(int) = 0;
    virtual void run(int, int, int, int, int) = 0;
};

#endif // ABSALGORITHM_H
