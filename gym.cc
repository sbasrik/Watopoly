#include <string>
#include <iostream>
#include <cstdlib>
#include "gym.h"
using namespace std;

int Gym::getPrice() {
    return this->price;
}

int Gym::getRent() {
    // roll dice * 10;
    srand (time(NULL));
    int roll = rand() % 10 + 1;
    cout << "You rolled " << roll << endl;
    return roll * 10;
}

std::string Gym::getName() {
    return this->name;
}

int getPosition() {
    return this->position;
}

std::string Gym::getOwner() {
    return this->owner
}

void Gym::setOwner(std::string owner) {
    this->owner = owner;
}

std::string getType() {
    return "GYM";
}