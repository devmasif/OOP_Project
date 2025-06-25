#include "Fire.h"

Fire::Fire(const sf::Vector2f& startPosition, std::string t) : isActive(true) {
    position = startPosition;
    if (!texture.loadFromFile(t)) {
        std::cerr << "Failed to load fire texture" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    speed = 5.0f;
}

void Fire::update() {
    if (isActive) {
        position.x += speed;
        sprite.setPosition(position);
        if (position.x > 1420) {
            isActive = false;
        }
    }
}

void Fire::draw(sf::RenderWindow& window) {
    if (isActive) {
        window.draw(sprite);
    }
}

void Fire::deactivate() {
    isActive = false;
}

bool Fire::active() const {
    return isActive;
}

void Fire::action() {
    // Implement action if needed
}

sf::FloatRect Fire::getBounds() const {
    return sprite.getGlobalBounds();
}
