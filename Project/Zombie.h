#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Elements.h"
#include <cstdlib>

class Zombie : public Elements {
public:
    Zombie(int frameCount, const std::string& basePath, float animationSpeed = 100.0f);

    virtual void update();
    virtual void action() = 0;
    virtual void draw(sf::RenderWindow& window);

    bool getisAlive() const;
    sf::FloatRect getBounds() const;
    void takeDamage(int damage);

protected:
    int health;
    float speed;
    bool isAlive;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Clock animationClock;
    int currentFrame;
    int totalFrames;
    float frameDuration;
    std::string textureBasePath;

    void loadTexture(int frameIndex);
    void updateAnimation();
};

#endif /* ZOMBIE_H */
