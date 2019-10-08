#include "connect.h"

//constructor
Connect::Connect(){
    id = 0;
    weight = 0;
}

//constructor
Connect::Connect(int i){
    id = i;
    weight = 0;
}

//constructor
Connect::Connect(int i, float w){
    id = i;
    weight = w;
}

//sets the id of Connect
void Connect::setId(int i){
    id = i;
}

//sets the weight of Connect
void Connect::setWeight(float d){
    weight = d;
}
