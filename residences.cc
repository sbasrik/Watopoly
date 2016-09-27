#include <string>
#include "residences.h"

int Residence::getPrice() {
    return this->price;
}

int Residence::getRent() {
    return this->rent;
}

std::string Residence::getName() {
    return this->name;
}

int Residence::getPosition() { 
    return this->position;
}

std::string Residence::getOwner() {
    return this->owner;
}

void Residence::setOwner() {
    this->owner = owner;
}

std::string getType() {
    return "RESIDENCE";
}