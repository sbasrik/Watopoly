#ifndef __WASHROOM_H__
#define __WASHROOM_H__

#include <string>
#include "improvement.h"

class Washroom: public Improvement {
    public:
        Washroom(Building *bp);
        double getPrice() override;
        double getRent() override;
        std::string getName() override;
        int getPosition() override;
};
#endif
