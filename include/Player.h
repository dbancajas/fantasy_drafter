#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include "datatypes.h"

using namespace std;

class Player {
public:
    explicit Player(){}
    Player(string n,float pts,string pos,float sal);

    inline const float & getPoints() const { return points; }
    inline const float & getSalary() const { return salary; }
    inline const string & getName() const { return name; }
    inline const string & getPos() const { return position; }

private:
    string name;
    float points;
    string position;
    float salary;
};



#endif


