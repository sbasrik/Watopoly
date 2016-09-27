#ifndef __CAFETERIA_H__
#define __CAFETERIA_H__

#include <string>
#include "improvement.h"
class Cafeteria: public Improvement {
    public:
        Cafeteria(Building *bp) Improvement{bp} {}
        double getPrice() override;
        double getRent() override;
        std::string getName() override;
        int getPosition() override;
};
#endif
