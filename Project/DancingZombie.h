#ifndef DANCINGZOMBIE_H
#define DANCINGZOMBIE_H

#include "Zombie.h"


class DancingZombie : public Zombie {
public:
    DancingZombie();

    void action() override;
};

#endif /* DANCINGZOMBIE_H */
