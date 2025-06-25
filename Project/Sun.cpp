#include "Sun.h"

Sun::Sun(bool fall) : falling(fall) {
    if (!texture.loadFromFile("../Images/sun.png")) {
        std::cout << "Failed to load sun texture" << std::endl;
    }
    sprite.setTexture(texture);
    resetPosition();
}

void Sun::resetPosition() {
    int x = 200 + rand() % 400;
    setPosition(x, 0);
    falling = true;
    waiting = false;
    waitClock.restart();
}

void Sun::update() {
    if (waiting) {
        if (waitClock.getElapsedTime().asSeconds() > 10) {
            resetPosition();
        }
    }
    else if (falling) {
        if (sunClock.getElapsedTime().asMilliseconds() > 50) {
            position.y += speed;
            sprite.setPosition(position);
            sunClock.restart();
            score += 25;
        }

        if (position.y > 120) {
            position.x = 1000;
            position.y = -20;
            sprite.setPosition(position);
            falling = false;
            waiting = true;
            waitClock.restart();
        }
    }
}

void Sun::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Sun::action() {
    // Implement action if needed
}
