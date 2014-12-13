#ifndef TEAM_H
#define TEAM_H

#include<iostream>
#include<vector>
#include<bitset>
#include<cassert>
#include "Player.h"
#include "datatypes.h"

using std::vector;
using std::cout;

class Team {

public:
   explicit Team();
   Team(const vector<Player> & p); 

   float getPoints() const;
   float points() const;
   float totalSalary() const;
   void  printInfo() const;
   bitset<BIT> getbs(void) const;
   int diff(const Team * t) const;

   void addPlayer(int player_idx);// adds player to team
   void engagebits();

private:

   vector<char> players; //contains index to players
   float totalpoints;
   float totalsalary;
   const vector<Player> & parray;
   bitset<BIT> bs;//bit set for players, used to calculate how 1 team is different from another

};
 
	

#endif

