#include "watopoly.h"
#include "building.h"
#include "player.h"
#include <iostream>
#include <string>
using namespace std;


Watopoly::Watopoly(bool load, bool test, string filename) {
   
    b = new Board(load, test, filename);
    play();
}


void Watopoly::play(){
	string input;
	while(true){
		cin >> input;
		if(input == "roll"){
			if(test){
				cin >> string roll1 >> string roll2;
				b->roll(roll1,roll2);
				continue;	
			}	
			b->roll();
		}
		else if(input == "trade") //sem code trade
		else if(input == "next") b->next();
		else if(input == "all")b->all();
		else if(input == "assets")b->assets(); //modify assets
		else if(input == "bankrupt")b->bankrupt(); //code bankrupt
		else if(input == "save"){
			cin >> string filename;
			b.save(filename);
		}
		else if(input == "improve")//sem codes improve
		else if(input == "mortgage")//sem codes mortgage
		else if(input == "unmortgage")//sem codes unmortgage
		else{
			cout << "Invalid input. type 'help' for the list of commands." << endl;
		}
	}
}
