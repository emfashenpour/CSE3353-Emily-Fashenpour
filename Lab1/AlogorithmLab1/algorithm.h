#ifndef ALGORITHM_H
#define ALGORITHM_H

//parent class
class Algorithm{
public:
    virtual void load(char*) = 0;
    virtual void execute() = 0;
    virtual void display() = 0;
    virtual void stats() = 0;
    virtual void select(int) = 0;
    virtual void save(char*) = 0;
    virtual void configure() = 0;
};

#endif // ALGORITHM_H
