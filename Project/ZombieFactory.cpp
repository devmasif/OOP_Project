#include "ZombieFactory.h"

Zombie* ZombieFactory::createZombie(std::string type) {
    if (type == "normal") {
        return new NormalZombie();
    }
    if (type == "football") {
        return new FootballZombie();
    }
    if (type == "dancing") {
        return new DancingZombie();
    }
    if (type == "flying") {
        return new FlyingZombie();
    }
    // Extend with other zombie types as needed
    return nullptr;
}
