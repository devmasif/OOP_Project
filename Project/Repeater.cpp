#include "Repeater.h"

Repeater::Repeater() : ShootingPlant(20), num(0) {
    loadTextures("../Images/card_repeaterpea.png", "../assets/Plants/RepeaterPea/RepeaterPea_0.png");
    setupSprites(280, 0);
}

void Repeater::updateAnimation() {
    if (textureClock.getElapsedTime().asMilliseconds() >= 40) {
        textureClock.restart();
        num = (num + 1) % 14;  // Assuming 13 frames of animation
        updateTexture("../assets/Plants/RepeaterPea/RepeaterPea_" + std::to_string(num) + ".png");
    }
}

void Repeater::updateTexture(const std::string& texturePath) {
    if (!dragTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }
}

void Repeater::update(Zombie** zombies, int zombieCount) {
    if (isPlanted) {
        updateAnimation();
        updateBullets(zombies, zombieCount);  // Now passes zombies and their count
        checkFireCondition();
    }
}

void Repeater::update() {
    // Implement specific updates for Repeater if needed
}

void Repeater::fire() {
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

void Repeater::checkFireCondition() {
    if (fireClock.getElapsedTime().asSeconds() >= 1) {
        fireClock.restart();
        fire();
    }
}

void Repeater::action() {
    // Implement actions specific to Repeater if needed
}
