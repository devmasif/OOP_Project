#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "Plant.h"
#include "Sun.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Sunflower : public Plant {
private:
    Sun s;

public:
    Sunflower();

    void update(Zombie** zombie, int ZombieCount);
    void update() override;
    void action() override;
};

#endif /* SUNFLOWER_H */
