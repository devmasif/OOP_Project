#include "FootballZombie.h"

FootballZombie::FootballZombie() : Zombie(4, "D:/OOP_Project/assets/Zombies/FootballZombie/footballzombie") {
    int lanes[5] = { 40, 140, 240, 340, 440 };
    int index = rand() % 5;
    position.y = lanes[index];
    position.x = 1100;
    sprite.setScale(1.f, 1.f);
    sprite.setPosition(position.x, position.y);
    health = 200;
    speed = 0.6f;
}

void FootballZombie::action() {
}
