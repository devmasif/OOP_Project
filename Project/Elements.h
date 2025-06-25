#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <SFML/Graphics.hpp>

class Elements {
protected:
    sf::Vector2f position;
    sf::Sprite sprite;

public:
    virtual void setPosition(float x, float y);
    virtual sf::Vector2f getPosition() const;
    virtual void draw(sf::RenderWindow& window);
    sf::Sprite getSprite();
    virtual void update() = 0;  // Pure virtual for updates per frame
    virtual void action() = 0;  // Pure virtual for specific element action
};

#endif /* ELEMENTS_H */
