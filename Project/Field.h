#ifndef FIELD_H
#define FIELD_H

#include <SFML/Graphics.hpp>

class Field {
private:
    sf::FloatRect* plantableBoxes;
    bool* isOccupied;
    int boxCount;
    sf::Vector2f boxSize;

public:
    Field();
    ~Field();

    void initializeField();
    bool isPlantableArea(const sf::Vector2f& position);
    void freeBox(const sf::Vector2f& position);
    sf::Vector2f snapToBox(const sf::Vector2f& position);
};

#endif /* FIELD_H */
