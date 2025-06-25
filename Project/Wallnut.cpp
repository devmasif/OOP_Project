#include "Wallnut.h"

Wallnut::Wallnut() : num(0) {
    loadTextures("../Images/card_wallnut.png", "../assets/plants/WallNut/WallNut/WallNut_0.png");
    setupSprites(140, 0);
}

void Wallnut::updateAnimation() {
    if (textureClock.getElapsedTime().asMilliseconds() >= 50) {
        textureClock.restart();
        num = (num + 1) % 16;  // Assuming 16 frames of animation
        updateTexture("../assets/plants/WallNut/WallNut/WallNut_" + std::to_string(num) + ".png");
    }
}

void Wallnut::updateTexture(const std::string& texturePath) {
    if (!displayTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }
    displaySprite.setTexture(displayTexture);
}

void Wallnut::update(Zombie** zombies, int zombieCount) {
    if (isPlanted) {
        updateAnimation();
    }
}

void Wallnut::update() {
    
}

void Wallnut::action() {
    // Implement any specific Wallnut actions if necessary
}
