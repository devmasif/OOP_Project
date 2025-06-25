#ifndef PLANT_H
#define PLANT_H
#include "Zombie.h"
#include "Elements.h"
#include "Field.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Plant : public Elements {
public:
    sf::Texture displayTexture, dragTexture;
    sf::Sprite displaySprite, dragSprite;
    sf::Clock textureClock;
    bool isDragging, isPlanted;
    sf::Vector2f dragOffset;
    int num;

    Plant();

    virtual void loadTextures(const std::string& displayPath, const std::string& dragPath);
    virtual void setupSprites(float x, float y);
    void handleEvent(sf::RenderWindow& window, sf::Event& event, Field& field);
    void plant(const sf::Vector2f& position);
    void checkZombies(Zombie** zombies, int zombieCount);
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) override;
};

#endif /* PLANT_H */
