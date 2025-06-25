#ifndef FOOTBALLZOMBIE_H
#define FOOTBALLZOMBIE_H

#include "Zombie.h"


class FootballZombie : public Zombie {
public:
    FootballZombie();

    void action() override;
};

#endif /* FOOTBALLZOMBIE_H */
#pragma once
