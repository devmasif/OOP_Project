#ifndef WALLNUT_H
#define WALLNUT_H

#include "Plant.h"
#include <SFML/Graphics.hpp>

class Wallnut : public Plant {
private:
    sf::Clock textureClock;
    int num;  // Frame number for animation

public:
    Wallnut();

    void updateAnimation();
    void updateTexture(const std::string& texturePath);
    void update(Zombie** zombies, int zombieCount) ;
    void update() override;
    void action() override;
};

#endif /* WALLNUT_H */
