#include "Elements.h"

void Elements::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    sprite.setPosition(position);
}

sf::Vector2f Elements::getPosition() const {
    return position;
}

void Elements::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Sprite Elements::getSprite() {
    return sprite;
}
