#include "Team.h"


Team::Team(const vector<Player> & p):parray(p){
	players.clear();
	totalpoints=0.0;
	totalsalary=0.0;
}

/*
float 
Team::getPoints() const { 
	return totalpoints; 
}


float 
Team::totalSalary() const {
   return totalsalary;
}
*/

void 
Team::printInfo() const {
	   cout<<"======"<<endl;
	   cout<<"points: "<<totalpoints<<endl;
	   cout<<"salary: "<<totalsalary<<endl;

	   cout<<"members:"<<endl;
	   for (vint_sz i=0; i <players.size();i++){
	   	   const Player & p=parray[players[i]];
		   cout<<p.getPos()<<": " <<p.getName()<<endl;
	   }
}

bitset<BIT> 
Team::getbs(void) const {
	return bs;
}
   
int 
Team::diff(const Team * t) const {
	return (bs | t->getbs()).count();
}


void 
Team::engagebits() {
   for(vint_sz i=0; i < players.size(); i++){
	   assert(players[i] < bs.size());
	   bs.set(players[i]);
   }
}

void 
Team::addPlayer(int player_idx) { //adds player to team
	totalsalary+=parray[player_idx].getSalary();
	totalpoints+=parray[player_idx].getPoints();
	players.push_back(player_idx);
}



