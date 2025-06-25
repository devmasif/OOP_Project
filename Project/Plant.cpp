#include "Plant.h"

Plant::Plant() : num(0), isDragging(false), isPlanted(false) {}

void Plant::loadTextures(const std::string& displayPath, const std::string& dragPath) {
    if (!displayTexture.loadFromFile(displayPath)) {
        std::cout << "Failed to load display image!" << std::endl;
    }
    if (!dragTexture.loadFromFile(dragPath)) {
        std::cout << "Failed to load drag image!" << std::endl;
    }
}

void Plant::setupSprites(float x, float y) {
    displaySprite.setTexture(displayTexture);
    displaySprite.setPosition(x, y);
    displaySprite.setScale(1.f, 1.f);

    dragSprite.setTexture(dragTexture);
    dragSprite.setScale(1.f, 1.f);
    dragSprite.setColor(sf::Color(255, 255, 255, 0)); // Initially make dragSprite invisible
}

void Plant::handleEvent(sf::RenderWindow& window, sf::Event& event, Field& field) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        if (displaySprite.getGlobalBounds().contains(mousePos)) {
            isDragging = true;
            dragOffset = mousePos - displaySprite.getPosition();
            dragSprite.setPosition(displaySprite.getPosition());
            dragSprite.setColor(sf::Color(255, 255, 255, 255)); // Make dragSprite visible
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        if (isDragging) {
            sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
            sf::Vector2f snapPos = field.snapToBox(mousePos - dragOffset);
            if (field.isPlantableArea(snapPos)) {
                plant(snapPos);
            }
            else {
                dragSprite.setColor(sf::Color(255, 255, 255, 0)); // Make invisible if not plantable
            }
            isDragging = false;
        }
    }

    if (event.type == sf::Event::MouseMoved && isDragging) {
        sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
        dragSprite.setPosition(mousePos - dragOffset);
    }
}

void Plant::plant(const sf::Vector2f& position) {
    setPosition(position.x, position.y);
    dragSprite.setPosition(position);
    isPlanted = true;
}

void Plant::checkZombies(Zombie** zombies, int zombieCount) {
    sf::FloatRect plantBounds = sprite.getGlobalBounds();

    for (int j = 0; j < zombieCount; ++j) {
        if (zombies[j]->getisAlive() && plantBounds.intersects(zombies[j]->getBounds())) {
            //   takeDamage(10);
            //    zombies[j]->performAttack();
        }
    }
}

void Plant::draw(sf::RenderWindow& window) {
    window.draw(displaySprite);
    if (isPlanted || dragSprite.getColor().a != 0) {
        window.draw(dragSprite);
    }
}
