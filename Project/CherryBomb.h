#ifndef CHERRYBOMB_H
#define CHERRYBOMB_H

#include "Plant.h"
#include <SFML/Graphics.hpp>

class CherryBomb : public Plant {
private:
    sf::Clock textureClock;
    int num;  // Frame number for animation

public:
    CherryBomb();

    void updateAnimation();
    void updateTexture(const std::string& texturePath);
    void update(Zombie** zombies, int zombieCount) ;
    void update() override;
    void action() override;
    void action(Zombie** zombies, int zombieCount);
};

#endif /* CHERRYBOMB_H */
