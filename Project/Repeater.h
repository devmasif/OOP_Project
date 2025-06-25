#ifndef REPEATER_H
#define REPEATER_H

#include "ShootingPlant.h"
#include <SFML/Graphics.hpp>

class Repeater : public ShootingPlant {
private:
    sf::Clock textureClock;
    int num;  // Frame number for animation

public:
    Repeater();

    void updateAnimation();
    void updateTexture(const std::string& texturePath);
    void update(Zombie** zombies, int zombieCount) ;
    void update() override;
    void fire() override;
    void checkFireCondition();
    void action() override;
};

#endif /* REPEATER_H */
