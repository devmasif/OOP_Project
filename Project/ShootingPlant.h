#ifndef SHOOTINGPLANT_H
#define SHOOTINGPLANT_H

#include "Plant.h"
#include "Fire.h"
#include <SFML/Graphics.hpp>

class ShootingPlant : public Plant {
protected:
    Fire** bullets;
    int maxBullets;
    int currentBulletCount;
    sf::Clock fireClock;

public:
    ShootingPlant(int maxBullets);
    virtual ~ShootingPlant();
    void updateBullets(Zombie** zombies, int zombieCount);
    virtual void fire() = 0; // Make fire a pure virtual function
    void draw(sf::RenderWindow& window) override;
};

#endif /* SHOOTINGPLANT_H */
