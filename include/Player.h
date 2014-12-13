#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include "datatypes.h"

using namespace std;

class Player {
public:
    explicit Player(){}
    Player(string n,float pts,string pos,float sal);

    inline float getPoints(){ return points; }
    inline float getSalary(){ return salary; }
    inline string getName(){ return name; }
    inline string pos() { return position; }

private:
    string name;
    float points;
    string position;
    float salary;
};



#endif


