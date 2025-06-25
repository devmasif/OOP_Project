#ifndef NORMALZOMBIE_H
#define NORMALZOMBIE_H

#include "Zombie.h"

class NormalZombie : public Zombie {
public:
    NormalZombie();

    void action() override;
};

#endif /* NORMALZOMBIE_H */
