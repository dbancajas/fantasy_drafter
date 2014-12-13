#include<vector>
#include "Player.h"

using std::vector;
using std::cout;

class Team {
public:
   Team(const vector<Player> & p):parray(p){
	players.clear();
	totalpoints=0.0;
	totalsalary=0.0;
   }

   float getPoints();
private:

   vector<char> players; //contains index to players
   float totalpoints;
   float totalsalary;
   const vector<Player> & parray;
   bitset<BIT> bs;//bit set for players
};
 
