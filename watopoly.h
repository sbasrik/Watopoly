#ifndef __WATOPOLY_H__
#define __WATOPOLY_H__

#include <string>
#include "board.h"

class Watopoly {
  	std::bool test;
	  Board *b;
  public:
    Watopoly(std::bool load, std::bool test, std::string filename);
    void play();
    
};
#endif
