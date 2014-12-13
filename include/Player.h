#include<string>

using namespace std;

class Player {
public:
    explicit Player(){}
    Player(string n,float pts,string pos,float sal):name(n),points(pts),position(pos), salary(sal){}
    inline float getPoints(){ return points; }
    inline float getSalary(){ return salary; }

private:
    string name;
    float points;
    string position;
    float salary;
};


