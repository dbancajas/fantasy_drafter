#include "Team.h"

float 
Team::getPoints() { 
	return totalpoints; 
}

float 
Team::points(){
	for(vint_sz i=0; i < players.size();i++)
	 totalpoints+=parray[players[i]].points;

 	return totalpoints;
}

float 
Team::salary(){
   for(vint_sz i=0; i < players.size();i++)
	totalsalary+=parray[players[i]].salary;

   return totalsalary;
}

void 
Team::printinfo(){
	   cout<<"======"<<endl;
	   cout<<"points: "<<totalpoints<<endl;
	   cout<<"salary: "<<totalsalary<<endl;

	   cout<<"members:"<<endl;
	   for (vint_sz i=0; i <players.size();i++){
	   	   const Player & p=parray[players[i]];
		   cout<<p.position<<": " <<p.name<<endl;
	   }
}

void 
Team::engagebits(){
   for(vint_sz i=0; i < players.size(); i++){
	   assert(players[i] < bs.size());
	   bs.set(players[i]);
   }
}

bitset<BIT> 
Team::getbs(void) const {
	return bs;
}
   
int 
Team::diff(const Team * t) {
	return (bs | t->getbs()).count();
}



