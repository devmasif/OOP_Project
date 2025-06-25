#include "Field.h"

Field::Field() : plantableBoxes(nullptr), isOccupied(nullptr), boxCount(0), boxSize(75, 100) {
    initializeField();
}

Field::~Field() {
    delete[] plantableBoxes;
    delete[] isOccupied;
}

void Field::initializeField() {
    int xCount = (980 - 250) / 80 + 1;
    int yCount = (570 - 80) / 100 + 1;
    boxCount = xCount * yCount;

    plantableBoxes = new sf::FloatRect[boxCount];
    isOccupied = new bool[boxCount]();

    int index = 0;
    for (int x = 250; x <= 980; x += 80) {
        for (int y = 80; y <= 570; y += 100) {
            plantableBoxes[index] = sf::FloatRect(x, y, boxSize.x, boxSize.y);
            isOccupied[index] = false;
            index++;
        }
    }
}

bool Field::isPlantableArea(const sf::Vector2f& position) {
    for (int i = 0; i < boxCount; i++) {
        if (plantableBoxes[i].contains(position) && !isOccupied[i]) {
            isOccupied[i] = true;
            return true;
        }
    }
    return false;
}

void Field::freeBox(const sf::Vector2f& position) {
    for (int i = 0; i < boxCount; i++) {
        if (plantableBoxes[i].contains(position)) {
            isOccupied[i] = false;
            break;
        }
    }
}

sf::Vector2f Field::snapToBox(const sf::Vector2f& position) {
    for (int i = 0; i < boxCount; i++) {
        if (plantableBoxes[i].contains(position)) {
            return sf::Vector2f(plantableBoxes[i].left, plantableBoxes[i].top);
        }
    }
    return position;
}
