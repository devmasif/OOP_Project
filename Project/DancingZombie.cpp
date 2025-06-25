#include "DancingZombie.h"

DancingZombie::DancingZombie() : Zombie(4, "D:/OOP_Project/assets/Zombies/DancingZombie/dancingzombie") {
    int lanes[5] = { 40, 140, 240, 340, 440 };
    int index = rand() % 5;
    position.y = lanes[index];
    position.x = 1100;
    sprite.setScale(1.f, 1.f);
    sprite.setPosition(position.x, position.y);
    health = 100;
    speed = 0.7f;
}

void DancingZombie::action() {
   
}
