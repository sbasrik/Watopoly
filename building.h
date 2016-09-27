#ifndef __BUILDING_H__
#define __BUILDING_H__

#include <string>

class Building {
   public:
//        explicit Building(std::string name, double price, double rent);
        virtual int getPrice();
        virtual int getRent();
        virtual std::string getName();
        virtual std::string getOwner();
        virtual int getPosition();
        virtual void setOwner(std::string owner);
    virtual std::string getType();
        virtual ~Building() = 0;
};
#endif
