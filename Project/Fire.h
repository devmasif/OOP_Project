#ifndef FIRE_H
#define FIRE_H

#include "Elements.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Fire : public Elements {
private:
    float speed;
    sf::Texture texture;
    bool isActive;

public:
    Fire(const sf::Vector2f& startPosition, std::string t);

    void update() override;
    void draw(sf::RenderWindow& window) override;
    void deactivate();
    bool active() const;
    void action();
    sf::FloatRect getBounds() const;
};

#endif /* FIRE_H */
