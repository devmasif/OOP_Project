#include "ShootingPlant.h"

ShootingPlant::ShootingPlant(int maxBullets) : Plant(), maxBullets(maxBullets), currentBulletCount(0) {
    bullets = new Fire * [maxBullets];
    for (int i = 0; i < maxBullets; ++i) {
        bullets[i] = nullptr;
    }
}

ShootingPlant::~ShootingPlant() {
    for (int i = 0; i < maxBullets; ++i) {
        delete bullets[i];
    }
    delete[] bullets;
}

void ShootingPlant::updateBullets(Zombie** zombies, int zombieCount) {
    for (int i = 0; i < maxBullets; ++i) {
        if (bullets[i] != nullptr && bullets[i]->active()) {
            bullets[i]->update();
            sf::FloatRect bulletBounds = bullets[i]->getBounds();

            for (int j = 0; j < zombieCount; ++j) {
                if (zombies[j]->getisAlive() && bulletBounds.intersects(zombies[j]->getBounds())) {
                    zombies[j]->takeDamage(25); // Damage value can be adjusted
                    bullets[i]->deactivate();
                    break; // Stop checking after a hit
                }
            }

            if (!bullets[i]->active()) {
                delete bullets[i];
                bullets[i] = nullptr;
                currentBulletCount--;
            }
        }
    }
}

void ShootingPlant::draw(sf::RenderWindow& window) {
    Plant::draw(window);  // Draw the plant itself
    for (int i = 0; i < maxBullets; ++i) {
        if (bullets[i] != nullptr) {
            bullets[i]->draw(window);  // Draw each bullet
        }
    }
}
