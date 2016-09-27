#ifndef __IMPROVEMENT_H__
#define __IMPROVEMENT_H__

#include "building.h"

class Improvement: public Building {
    protected:
        Building *bp;
    public:
        Improvement(Building *bp): bp{bp} {}
        virtual ~Improvement() { delete bp; }
};
#endif
