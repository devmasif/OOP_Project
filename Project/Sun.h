#ifndef SUN_H
#define SUN_H

#include "Elements.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Sun : public Elements {
private:
    bool falling;
    int speed = 1;
    sf::Texture texture;
    sf::Clock sunClock, waitClock;
    bool waiting = false;
    int score;

public:
    Sun(bool fall = true);

    void resetPosition();
    void update();
    void draw(sf::RenderWindow& window) override;
    void action();
};

#endif /* SUN_H */
