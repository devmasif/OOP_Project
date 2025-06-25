#ifndef YARD_H
#define YARD_H

#include <SFML/Graphics.hpp>

class Yard {
private:
    int sunScore;
    sf::Texture scoreTexture;
    sf::Sprite scoreSprite;

public:
    Yard();
    void increaseSun(int amount);
    void decreaseSun(int amount);
    void updateScoreDisplay();
    void draw(sf::RenderWindow& window);
    int getSunScore() const;
};

#endif // YARD_H
