#include "NormalZombie.h"

NormalZombie::NormalZombie() : Zombie(21, "D:/OOP_Project/assets/Zombies/NormalZombie/Zombie/Zombie_") {
    int lanes[5] = { 40, 140, 240, 340, 440 };
    int index = rand() % 5;
    position.y = lanes[index];
    position.x = 1100;
    sprite.setScale(1, 1.f);
    sprite.setPosition(position.x, position.y);
    health = 100;
    speed = 0.5f;
}

void NormalZombie::action() {
    
}
