#ifndef FLYINGZOMBIE_H
#define FLYINGZOMBIE_H

#include "Zombie.h"

class FlyingZombie : public Zombie {
public:
    FlyingZombie();

    void action() override;
};

#endif /* FLYINGZOMBIE_H */
