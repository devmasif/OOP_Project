#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "ShootingPlant.h"
#include <SFML/Graphics.hpp>

class Peashooter : public ShootingPlant {
private:
    sf::Clock textureClock;
    int num;  // Frame number for animation

public:
    Peashooter();

    void updateAnimation();
    void updateTexture(const std::string& texturePath);
    void update(Zombie** zombies, int zombieCount) ;
    void update() override;
    void fire() override;
    void checkFireCondition();
    void action() override;
};

#endif /* PEASHOOTER_H */
