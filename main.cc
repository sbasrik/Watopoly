#include "player.h"
#include <iostream>
using namespace std;
int main(){
	Player ahmet{"ahmet",'A'};
	cout << ahmet.getMoney() << endl;
	cout << ahmet.getPosition() << endl;
	ahmet.setPosition(50);
	cout << ahmet.getPosition() << endl;
	ahmet.setMoney(1);
	cout << ahmet.getMoney() << endl;
	ahmet.bankrupt();
	cout << ahmet.getMoney() << endl;
}
