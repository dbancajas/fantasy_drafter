#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cassert>
#include <algorithm>
#include <bitset>
#include <omp.h>
#include <string.h>

using namespace std;

typedef vector<int>::size_type vint_sz;
typedef vector<vector<int> >::size_type vvint_sz;
typedef vector<int>::const_iterator vint_itr;
typedef vector<vector<int> >::const_iterator vvint_itr;

#define BIT 250


//vector<int> people;
//vector<int> combination;
//

//as you can see, everything is public for now as I am creating this in 3 hours before the game.
//I will add appropriate abstraction/encapsulation once I get the algorithm correct.
class Player {
public:
    Player(){}
    Player(string n,float pts,string pos,float sal):name(n),points(pts),position(pos), salary(sal){}

    string name;
    float points;
    string position;
    float salary;
};

class Team {
public:
   Team(const vector<Player> & p):parray(p){
	players.clear();
	totalpoints=0.0;
	totalsalary=0.0;
   }

   float getPoints() { 
	   return totalpoints; 
   }

   float points(){
	   for(vint_sz i=0; i < players.size();i++)
		   totalpoints+=parray[players[i]].points;

	  return totalpoints;
   }

   float salary(){
	   for(vint_sz i=0; i < players.size();i++)
	 	totalsalary+=parray[players[i]].salary;

	   return totalsalary;
   }

   void printinfo(){
	   cout<<"======"<<endl;
	   cout<<"points: "<<totalpoints<<endl;
	   cout<<"salary: "<<totalsalary<<endl;

	   cout<<"members:"<<endl;
	   for (vint_sz i=0; i <players.size();i++){
	   	   const Player & p=parray[players[i]];
		   string tabs = p.name.length()<12? "\t\t":"\t";
		   float  value = p.points/p.salary * 1000.0;
		   cout<<p.position<<": " <<p.name<<tabs<<p.points<<"\t$"<<p.salary<<"\t"<<value<< endl;
	   }

   }

   void engagebits(){
	   for(vint_sz i=0; i < players.size(); i++){
		   assert(players[i] < bs.size());
		   //if (players[i] < bs.size()){
//
//		   }
		   bs.set(players[i]);
	   }

   }

   bitset<BIT> getbs(void) const {
	   return bs;
   }
   
   int diff(const Team * t) {
	   return (bs | t->getbs()).count();
   }

   vector<unsigned char> players; //contains index to players
   float totalpoints;
   float totalsalary;
   const vector<Player> & parray;
   bitset<BIT> bs;//bit set for players
};
 
  vector<Player> players;
  vector<Team *> teams;

void pretty_print(const vector<int>& v) {
  static int count = 0;
  cout << "combination no " << (++count) << ": [ ";
  for (vector<int>::size_type i = 0; i < v.size(); ++i) { cout << v[i] << " "; }
  cout << "] " << endl;
}

void get_1combo(const vector<int>& v, vector<int> & dest) {
  for (vector<int>::size_type i = 0; i < v.size(); ++i) { 
	  dest.push_back( v[i]) ; 
  }
}


void print_comb(vector<int> & comb){
	for (vint_itr i=comb.begin(); i!=comb.end(); i++)
		cout<<(*i)<<" ";
	cout<<endl;
}

void go(int offset, int k, const vector<int>& source, vector<int>& tmp, vector<vector<int> >& combs) {
 
  if (k == 0) {
    //pretty_print(tmp);
    vector<int> newc;
    get_1combo(tmp,newc);
    combs.push_back(newc);

    return;
  }
  for (vector<int>::size_type i = offset; i <= source.size() - k; ++i) {
    tmp.push_back(source[i]);
    go(i+1, k-1, source,tmp, combs);
    tmp.pop_back();
  }
}

void print_all(const vector<vector<int> > & combs){

	for(vector<vector<int> >::const_iterator i = combs.begin() ; i != combs.end(); i++){
		for (vint_itr j=i->begin(); j != i->end(); j++){
			cout<<*j<<" ";
		}
		cout<<endl;
	}
}

void csv_reader(vector<Player> & players, string datafile, int multiplier){
    //std::ifstream  data("data/projections.csv");
    //std::ifstream  data("data/12-13-2014_rotowire.csv");
    std::ifstream  data(datafile.c_str());


    std::string line;
    while(std::getline(data,line))
    {
	int i=0;
        stringstream  lineStream(line);
        string        cell;
        Player p;

        while(std::getline(lineStream,cell,','))
        {
	    i++;
	    if (i == 1){
		p.name = cell;
	    }
	    else if (i==2){
		p.position = cell;
  	    }
	    else if (i==3){
		//cell = cell.substr(0, cell.size()-1); //need to fix this for rotogrinders
		cell = cell.substr(0, cell.size());
		p.salary = atof(cell.c_str())*multiplier;
	    }
	    else if (i==4){
		p.points = atof(cell.c_str());
	    }

  //          cout<<"cell: "<<cell<<" "<<endl;

        }
	players.push_back(p);
	//cout<<endl;
#ifdef DEBUG
	cout<<p.name<<":"<<p.salary<<" "<<p.points<<endl;
#endif
    }

}

void print_combs(vector<vector<int> > c,const vector<Player> & p){
	int cnt=0;
	for(vvint_sz i=0; i < c.size(); i++){
		float totalpoints=0.0;
		float totalsalary=0.0;

		for(vvint_sz j=0; j < c[i].size(); j++){
			totalpoints+=p[c[i][j]].points;
			totalsalary+=p[c[i][j]].salary;
		}
		cout<<++cnt<<": "<<(totalpoints/totalsalary)*1000.0<<endl;
	}

}
   

struct myclass {
	bool operator() (vector<int> a, vector<int> b){
		float tp1=0.0;
		float tp2=0.0;
		float ts1=0.0;
		float ts2=0.0;

		for(vint_sz i=0;i<a.size();i++){
			tp1+=players[a[i]].points;
			ts1+=players[a[i]].salary;
		}

		for(vint_sz i=0;i<b.size();i++){
			tp2+=players[b[i]].points;
			ts2+=players[b[i]].salary;
		}

		return (tp1/ts1 > tp2/ts2);

	}

} mysorter;

struct teamsort {
	bool operator() (Team *a, Team *b){
		return a->getPoints() > b->getPoints();
	}
} teamsorter;

static float progress = 0.0;
void progress_bar(float prog, int teamsize){

	progress += prog;
	//cout<<"progress: "<<progress<<endl;

	//while (progress < 1.0) {
	    int barWidth = 70;

	    std::cout << "[";
	    int pos = barWidth * progress;
	    for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "=";
		else if (i == pos) std::cout << ">";
		else std::cout << " ";
	    }
	    std::cout << "] " << int(progress * 100.0) << " "<< teamsize <<" %\r";
	    std::cout.flush();

	    //progress += 0.16; // for demonstration only
	//}
	//cout << std::endl;


}

//this function will segregate teams into different buckets which depend on the "hamming distance" with the top team
void Hedge(vector<Team *>& teams, vector<Team *>& a_list){
	
	//put the top team as the seed
	assert(!teams.empty());

	a_list.push_back(teams[0]);

	int unique_players = 10;//there are currently 10 unique players
	unsigned int standard=5;//we want another 10 unique playeres to join the group

	for (vector<Team *>::size_type i=1; i < teams.size(); i++){//1-pass only
		bitset<BIT> current=0;
		bitset<BIT> newteam=teams[i]->getbs();

		for (vector<Team *>::size_type j=0; j < a_list.size(); j++){
			current |= a_list[j]->getbs();
		}

		if ( ((newteam | current).count()-current.count()) >= standard){//if passed
			a_list.push_back(teams[i]);
		}
	}

	cout<<"# Hedged positions:"<<a_list.size()<<endl;
	cout<<"Range of scores:"<<a_list[0]->getPoints()<<" - " <<a_list[a_list.size()-1]->getPoints()<<endl;

	  for (vector<Team *>::size_type i=0; i < a_list.size(); i++){
		  a_list[i]->printinfo();
	  }
}

enum PARAM { MULT, DATAFILE,  INVALID_PARAM };

struct config {
	int mult;
	string datafile;
};

config  parse_args(int argc, char * argv[]){
	string m = "--multiplier";
	string n = "--datafile";

	config a;

	for (int i = 0; i < argc; i++){
		if (strcmp(argv[i],m.c_str())==0){
			assert(i+1<argc); //see if there is an integer after
			a.mult = atoi(argv[i+1]);  
		}
		else if (DATAFILE && strcmp(argv[i],n.c_str())==0){
			assert(i+1<argc); //see if there is an integer after
			a.datafile = string(argv[i+1]);
		}
	}
	return a;
}
//TODO:
//Add option to disable player ID
//

int main(int argc, char * argv[]) {
  //int n = 5, k = 3;
  vector< vector<int> > combs;
  vector<int> source;
  vector<int> tmp;//temporary storage needed by algorithm

  int cutoff = 60;//limit combinations based on value;
  int num_threads=4;

  vector<Team *> a_list;
  vector<vector<Team *> > teams_omp;

  vector<int> Ce;
  vector<int> SF;
  vector<int> SG;
  vector<int> PF;
  vector<int> PG;

  vector<unsigned long long int> bins(11,0);//0 - <310, 1 - <320, ... , < 420

  vector<vector<int> > Ce_comb;
  vector<vector<int> > SF_comb;
  vector<vector<int> > SG_comb;
  vector<vector<int> > PF_comb;
  vector<vector<int> > PG_comb;

  config conf = parse_args(argc,argv);
  int multiplier=1;

  if (argc < 2)
	  multiplier=1;
  else 
	  multiplier = conf.mult;
	  
  assert(multiplier>0);
	  
  string datafile=conf.datafile;;
  assert(datafile.length()>0);
		 


  //for (int i = 0; i < n; ++i) { source.push_back(i*3); }
  //go(0, k,source, tmp, combs);

  //print_all(combs);

  //Scan Player
  //
  csv_reader(players,datafile,multiplier);
  //Segrate Positions
  for (vector<int>::size_type  i=0; i < players.size();i++){
	if (players[i].position == "C")
		Ce.push_back(i);
	else if (players[i].position == "SF")
		SF.push_back(i);
	else if (players[i].position == "PF")
		PF.push_back(i);
	else if (players[i].position == "PG")
		PG.push_back(i);
	else if (players[i].position == "SG")
		SG.push_back(i);
  }
  
  //Get Combinations
  go(0,1,Ce,tmp,Ce_comb);
  go(0,2,SF,tmp,SF_comb);
  go(0,2,SG,tmp,SG_comb);
  go(0,2,PF,tmp,PF_comb);
  go(0,2,PG,tmp,PG_comb);

  cout<<"Sizes: "<<endl;
  cout<<"Centers: "<<Ce_comb.size()<<endl;
  cout<<"SF: "<<SF_comb.size()<<endl;
  cout<<"SG: "<<SG_comb.size()<<endl;
  cout<<"PF: "<<PF_comb.size()<<endl;
  cout<<"PG: "<<PG_comb.size()<<endl;
  cout<<endl;

  //sort the arrays first
  //
  sort(Ce_comb.begin(),Ce_comb.end(), mysorter);
  sort(SF_comb.begin(),SF_comb.end(), mysorter);
  sort(SG_comb.begin(),SG_comb.end(), mysorter);
  sort(PF_comb.begin(),PF_comb.end(), mysorter);
  sort(PG_comb.begin(),PG_comb.end(), mysorter);

  SF_comb.erase(SF_comb.begin()+cutoff, SF_comb.end());
  SG_comb.erase(SG_comb.begin()+cutoff, SG_comb.end());
  PF_comb.erase(PF_comb.begin()+cutoff, PF_comb.end());
  PG_comb.erase(PG_comb.begin()+cutoff, PG_comb.end());

  /*print_combs(Ce_comb,players)k
  cout<<"centers end"<<endl;
  print_combs(SF_comb,players);
  cout<<"SF end"<<endl;
  print_combs(SG_comb,players);
  cout<<"SG end"<<endl;*/

  //We need to prune these combinations ... 

  //Big-Loop, Adding each team that meets the score
  //
  float teamsize = Ce_comb.size() *  SF_comb.size() *  SG_comb.size() *  PF_comb.size() *  PG_comb.size();
  
  cout<<"there are "<< teamsize<<" teams.."<<endl;
  
  
  cout<<"iterating ... "<<endl; 

  teams_omp.resize(PF_comb.size());
  //omp_set_num_threads(4);
  for (vvint_sz i = 0;i < Ce_comb.size(); i++){
  	for (vvint_sz j = 0; j < SF_comb.size(); j++){
  		for (vvint_sz k = 0; k < SG_comb.size() ; k++){
  			#pragma omp parallel for 
  			for (vvint_sz l = 0;l < PF_comb.size() ;l++){
  				for (vvint_sz m = 0 ; m < PG_comb.size() ;m++){
					//5 for loops here for each position
					Team *t = new Team(players);

					//Centers
					for(vint_sz n = 0; n < Ce_comb[i].size(); n++)
						t->players.push_back(Ce_comb[i][n]);

					//SF
					for(vint_sz n = 0; n < SF_comb[j].size(); n++)
						t->players.push_back(SF_comb[j][n]);

					//SG
					for(vint_sz n = 0; n < SG_comb[k].size(); n++)
						t->players.push_back(SG_comb[k][n]);

					//PF
					for(vint_sz n = 0; n < PF_comb[l].size(); n++)
						t->players.push_back(PF_comb[l][n]);

					//PG
					for(vint_sz n = 0; n < PG_comb[m].size(); n++)
						t->players.push_back(PG_comb[m][n]);

					float salary = t->salary();
					float points = t->points();


					if (points > 250.0 && salary<=60000 && salary > 59000){
						//t->printinfo();
						//#pragma omp critical
						teams_omp[l].push_back(t);
						//bins[int((points-300)/10)]++;
					}
					else 
						delete t;
				}
			}
		}
	}
	//progress_bar((teamsize/Ce_comb.size())/teamsize, teams.size());
	progress_bar((teamsize/Ce_comb.size())/teamsize, teams.size());
  }
  cout<<endl;

  for(vector<vector<Team *> >::size_type i=0; i < teams_omp.size();i++){
	  copy(teams_omp[i].begin(), teams_omp[i].end(), back_inserter(teams));
  }


  cout<<"There are "<<teams.size()<<" possible teams"<<endl;

  cout<<"sorting "<< teams.size()<<" teams .. "<<endl;
	  
  sort(teams.begin(), teams.end(), teamsorter);

  cout<<"top 20 team points"<<endl;

  for (vector<Team *>::size_type i=0; i < 20; i++){
	  cout<<i<<": "<<teams[i]->getPoints()<<endl;
  }

  cout<<"Getting ready to hedge positions..."<<endl;

  for (vector<Team *>::size_type i=0; i < teams.size(); i++){
	  teams[i]->engagebits();
  }

  cout<<"Done bit setting.."<<endl;

  /*for (vector<Team *>::size_type i=0; i < 20; i++){
	  teams[i]->printinfo();
  }*/
  //
  //Sort the team array
  //
  //Segregate to arrays with Hamming distance
  //
  //


  //for(int i=0; i< 5; i++){
//	cout<<players[i].name<<" "<<players[i].salary<<" "<<players[i].points<<endl;
 // }

  cout<<"Hedging ..."<<endl;
  Hedge(teams,a_list);
 

  for (vector<Team *>::size_type i=0; i < teams.size(); i++){
	  delete teams[i];
  }

  return 0;
}
