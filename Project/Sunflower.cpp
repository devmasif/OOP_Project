#include "Sunflower.h"

Sunflower::Sunflower() {
    loadTextures("../Images/card_sunflower.png", "../assets/plants/sunFlower/sunFlower_0.png");
    setupSprites(0, 0);
}

void Sunflower::update(Zombie** zombie, int ZombieCount) {
    if (textureClock.getElapsedTime().asMilliseconds() >= 50) {
        textureClock.restart();
        num = (num + 1) % 17;
        std::string texturePath = "../assets/plants/sunFlower/sunFlower_" + std::to_string(num) + ".png";
        if (!dragTexture.loadFromFile(texturePath)) {
            std::cout << "Failed to load texture: " << texturePath << std::endl;
        }
    }
}

void Sunflower::update() {
    // Implement specific updates for Sunflower if needed
}

void Sunflower::action() {
    s.update();
}
