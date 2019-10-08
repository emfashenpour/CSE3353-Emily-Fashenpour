#ifndef CONNECT_H
#define CONNECT_H

//Object class that will store the connections of one node
//to others. Int variable for id and float var for weight
class Connect{
public:
    Connect();
    Connect(int);
    Connect(int, float);
    void setId(int);
    void setWeight(float);

    int id;
    float weight;
};

#endif // CONNECT_H
