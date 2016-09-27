#include <string>
#include <algorithm>
#include <vector>
#include "player.h"
using namespace std;

Player::Player(std::string givename, const char piece):name{givename},piece{piece}{
	money = 500; //pre-determined global const
	position = 0;
	    cups = 0;
	timsCard = 0;
}

int Player::getMoney(){
	return money;
}

void Player::changeCups(int change){
    cups += change;
}

const char Player::getPiece(){
	return piece;
}

const string Player::getName(){
	return name;
}

void Player::setMoney(int newmoney){
	money = newmoney;
}

std::vector <int> Player::getAssets(){
	return buildings;	
}

int Player::getTims(){
	return timsCard;
}

void Player::setTims(const int newAmt){
	timsCard = newAmt;
}

void Player::addTims(){
	timsCard++;
}

void Player::remTims(){
        timsCard--;
}

void Player::bankrupt(){
	alive = false;
	money = 0;
	buildings.clear();
}

int Player::getPosition(){
	return position;
}

void Player::setPosition(const int newpos){
	position = newpos;
}

int Player::getResNum(){
	return resNum;
}

void Player::addRes(){ 
	resNum++;
}

void Player::remRes(){
        resNum--;
}

void Player::attachBuilding(const int building){
	buildings.emplace_back(building);
}

void Player::detachBuilding(const int building){
	buildings.erase(std::remove(buildings.begin(),
 				buildings.end(), building), buildings.end());
}
