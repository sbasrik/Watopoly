#ifndef __NON_PROPERTY_H__
#define __NON_PROPERTY_H__

#include "player.h"

const int OSAP_MONEY = 200;
const int COOP_FEE = 150;
const int TUITION = 300;
const int NUM_OF_SQUARES = 40;
const int DC_TIMS_LINE_POSITION = 9;

class NonProperty{

    int numOfCups = 0;

    public:
 
    void changeNumOfCups(int amount);
    int getNumOfCups();
    static void collectOsap(Player &p);
    // static void DCTimsLine(Player &p);
    static void goToTims(Player &p);
    // static void gooseNesting(Player &p);
    static void tuition(Player &p);
    static void coopFee(Player &p);
    static void slc(Player &p);
    static void needlesHall(Player &p);
    
};

#endif
