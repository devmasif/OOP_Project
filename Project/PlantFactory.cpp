#include "PlantFactory.h"

Plant* PlantFactory::createPlant(const std::string& type) {
    if (type == "Peashooter") return new Peashooter();
    if (type == "Sunflower") return new Sunflower();
    if (type == "Repeater") return new Repeater();
    if (type == "SnowPea") return new SnowPea();
    if (type == "Wallnut") return new Wallnut();
    if (type == "CherryBomb") return new CherryBomb();
    // Add more plant types as necessary
    return nullptr;
}