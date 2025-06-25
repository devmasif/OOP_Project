#ifndef PLANT_FACTORY_H
#define PLANT_FACTORY_H

#include <string>
#include "Plant.h" // Include the header file for the base Plant class
#include "Peashooter.h" // Include the header file for Peashooter class
#include "Sunflower.h" // Include the header file for Sunflower class
#include "Repeater.h" // Include the header file for Repeater class
#include "SnowPea.h" // Include the header file for SnowPea class
#include "Wallnut.h" // Include the header file for Wallnut class
#include "CherryBomb.h" // Include the header file for CherryBomb class

class PlantFactory {
public:
    static Plant* createPlant(const std::string& type);
};

#endif // PLANT_FACTORY_H
