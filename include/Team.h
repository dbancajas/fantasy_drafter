#ifndef TEAM_H
#define TEAM_H

#include<iostream>
#include<vector>
#include<bitset>
#include "Player.h"

using std::vector;
using std::cout;

class Team {

public:
   explicit Team();
   Team(const vector<Player> & p); 

   float getPoints();
   float points();
   float totalSalary();
   void  printInfo();

private:

   vector<char> players; //contains index to players
   float totalpoints;
   float totalsalary;
   const vector<Player> & parray;
   bitset<BIT> bs;//bit set for players
};
 
	

#endif

#include<vector>
#include "Player.h"


