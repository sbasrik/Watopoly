#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include <vector>
class Player{
	const std::string name;
	int money;
	int position;
	int resNum;
    int cups;
	int timsCard;
	bool alive;
	const char piece;	
	std::vector <int> buildings;
  public:
	Player(const std::string givename, const char piece);
	void changeCups(int change);
    const std::string getName();	
	const char getPiece();
	int getMoney();
	void setMoney(const int newmoney);
	void bankrupt();
	int getPosition();
	void setPosition(const int newpos);
	int getResNum();
	void addRes();
	void remRes();
	int getTims();
	void addTims();
	void remTims();
	void setTims(const int newAmt); 	
	void attachBuilding(const int building);
	void detachBuilding(const int building);	
	std::vector <int> getAssets();
};
#endif
