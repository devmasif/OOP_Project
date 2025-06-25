#ifndef SNOWPEA_H
#define SNOWPEA_H

#include "ShootingPlant.h"
#include <SFML/Graphics.hpp>

class SnowPea : public ShootingPlant {
private:
    sf::Clock textureClock;
    int num;  // Frame number for animation

public:
    SnowPea();

    void updateAnimation();
    void updateTexture(const std::string& texturePath);
    void update(Zombie** zombies, int zombieCount) ;
    void update() override;
    void fire() override;
    void checkFireCondition();
    void action() override;
};

#endif /* SNOWPEA_H */
