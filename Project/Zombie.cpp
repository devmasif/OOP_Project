#include "Zombie.h"

Zombie::Zombie(int frameCount, const std::string& basePath, float animationSpeed)
    : health(100), speed(0.5f), isAlive(true), currentFrame(0),
    totalFrames(frameCount), frameDuration(animationSpeed), textureBasePath(basePath) {
    loadTexture(currentFrame);
    sprite.setPosition(position.x, position.y);
}

void Zombie::loadTexture(int frameIndex) {
    std::string framePath = textureBasePath + std::to_string(frameIndex) + ".png";
    if (!texture.loadFromFile(framePath)) {
        std::cout << "Failed to load texture from: " << framePath << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
}

void Zombie::updateAnimation() {
    if (animationClock.getElapsedTime().asMilliseconds() >= frameDuration) {
        currentFrame = (currentFrame + 1) % totalFrames;
        loadTexture(currentFrame);
        animationClock.restart();
    }
}

void Zombie::update() {
    if (isAlive) {
        updateAnimation();
        position.x -= speed;
        sprite.setPosition(position);
    }
}

void Zombie::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Zombie::getisAlive() const {
    return isAlive && health > 0;
}

sf::FloatRect Zombie::getBounds() const {
    return sprite.getGlobalBounds();
}

void Zombie::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        isAlive = false;
        sprite.setColor(sf::Color(255, 255, 255, 128));
    }
}
