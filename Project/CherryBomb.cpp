#include "CherryBomb.h"

CherryBomb::CherryBomb() : num(0) {
    loadTextures("../Images/card_cherrybomb.png", "../assets/plants/CherryBomb/CherryBomb_0.png");
    setupSprites(350, 0);
}

void CherryBomb::updateAnimation() {
    if (textureClock.getElapsedTime().asMilliseconds() >= 50) {
        textureClock.restart();
        num = (num + 1) % 7;  
        updateTexture("../assets/plants/CherryBomb/CherryBomb_" + std::to_string(num) + ".png");
    }
}

void CherryBomb::updateTexture(const std::string& texturePath) {
    if (!displayTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }
    displaySprite.setTexture(displayTexture);
}

void CherryBomb::update(Zombie** zombies, int zombieCount) {
    if (isPlanted) {
        updateAnimation();
        action(zombies, zombieCount);
    }
}

void CherryBomb::update() {
}

void CherryBomb::action(Zombie** zombies, int zombieCount) {
    const float explosionRadius = 100.0f; // Define the explosion radius

    // Loop through all zombies to check if they are within the explosion radius
    for (int i = 0; i < zombieCount; ++i) {
        sf::Vector2f zombiePosition = zombies[i]->getPosition();
        sf::Vector2f cherryBombPosition = getPosition();

        // Calculate the distance between the zombie and the CherryBomb
        float distance = std::sqrt(std::pow(zombiePosition.x - cherryBombPosition.x, 2) +
            std::pow(zombiePosition.y - cherryBombPosition.y, 2));

        // Check if the zombie is within the explosion radius
        if (distance <= explosionRadius) {
            // Apply damage to the zombie
            zombies[i]->takeDamage(100); // Adjust the damage value as needed
        }
    }
}

void CherryBomb::action() {

}

