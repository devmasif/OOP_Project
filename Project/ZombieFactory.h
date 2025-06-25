#ifndef ZOMBIEFACTORY_H
#define ZOMBIEFACTORY_H

#include "Zombie.h"
#include "NormalZombie.h"
#include "FootballZombie.h"
#include "DancingZombie.h"
#include "FlyingZombie.h"

class ZombieFactory {
public:
    static Zombie* createZombie(std::string type);
};

#endif /* ZOMBIEFACTORY_H */
