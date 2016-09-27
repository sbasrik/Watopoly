#include <iostream>
#include <string>
#include <fstream>
#include "player.h"
#include <vector>
using namespace std;

int main(){
		
}

/*
void canBuy(const player &p, const int cost){
	return p.getMoney() >= cost
}
*/

//prints all the assets of the given player
void assets(Player &p){
	vector<int> assets = p.getAssets();
	cout << p.getName() << " has $" << p.getMoney() << " and owns the buildings:" << endl;
	for(int a:assets){
		cout << a << endl;
	}
	cout << "and " << p.getResNum() << " residences." << endl;		
}


// saves the data to given filename as described in watopoly.pdf
void save(const string filename){
	ofstream out;
	out.open(filename);
	out << players.size() << endl;
	for(Player &p:players){
		cout << p.getName() << " " << p.getPiece() << " " << p.getTims() << " " << p.getMoney()
				<< " " << p.getPosition();
	}
	for(Building &b:buildings){
		cout << b.getName() << " " << b.getOwner() << " " << b.improveCount() << endl;
	} 
}


//goes through the players vector to print their assets.
void all(){
	for(Player &p:players){
		assets(p);
	}
}
