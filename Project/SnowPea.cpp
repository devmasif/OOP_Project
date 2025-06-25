#include "SnowPea.h"

SnowPea::SnowPea() : ShootingPlant(20), num(0) {
    loadTextures("../Images/card_snowpea.png", "../assets/Plants/SnowPea/SnowPea_0.png");
    setupSprites(210, 0);
}

void SnowPea::updateAnimation() {
    if (textureClock.getElapsedTime().asMilliseconds() >= 40) {
        textureClock.restart();
        num = (num + 1) % 15;  // Assuming 14 frames of animation
        updateTexture("../assets/Plants/SnowPea/SnowPea_" + std::to_string(num) + ".png");
    }
}

void SnowPea::updateTexture(const std::string& texturePath) {
    if (!dragTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }
}

void SnowPea::update(Zombie** zombies, int zombieCount) {
    if (isPlanted) {
        updateAnimation();
        updateBullets(zombies, zombieCount);
        checkFireCondition();
    }
}

void SnowPea::update() {
    
}

void SnowPea::fire() {
    if (currentBulletCount < maxBullets) {
        for (int i = 0; i < maxBullets; ++i) {
            if (bullets[i] == nullptr) {
                bullets[i] = new Fire(sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width + 55, 0), "../assets/Bullets/PeaIce/icepea.png");
                currentBulletCount++;
                break;
            }
        }
    }
}

void SnowPea::checkFireCondition() {
    if (fireClock.getElapsedTime().asSeconds() >= 1) {
        fireClock.restart();
        fire();
    }
}

void SnowPea::action() {
    
}
