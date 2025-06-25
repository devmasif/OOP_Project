#include "Peashooter.h"

Peashooter::Peashooter() : ShootingPlant(10), num(0) {
    loadTextures("../Images/card_peashooter.png", "../assets/plants/Peashooter/Peashooter_0.png");
    setupSprites(70, 0);
}

void Peashooter::updateAnimation() {
    if (textureClock.getElapsedTime().asMilliseconds() >= 40) {
        textureClock.restart();
        num = (num + 1) % 13;
        updateTexture("../assets/Plants/Peashooter/Peashooter_" + std::to_string(num) + ".png");
    }
}

void Peashooter::updateTexture(const std::string& texturePath) {
    if (!dragTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }
}

void Peashooter::update(Zombie** zombies, int zombieCount) {
    if (isPlanted) {
        updateAnimation();
        updateBullets(zombies, zombieCount);
        checkFireCondition();
    }
}

void Peashooter::update() {
    // Implement specific updates for Peashooter if needed
}

void Peashooter::fire() {
    if (currentBulletCount < maxBullets) {
        for (int i = 0; i < maxBullets; ++i) {
            if (bullets[i] == nullptr) {
                bullets[i] = new Fire(sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width + 55, 0), "../assets/Bullets/PeaNormal/pea.png");
                currentBulletCount++;
                break;
            }
        }
    }
}

void Peashooter::checkFireCondition() {
    if (fireClock.getElapsedTime().asSeconds() >= 2) {
        fireClock.restart();
        fire();
    }
}

void Peashooter::action() {
    // Implement actions specific to Peashooter if needed
}
