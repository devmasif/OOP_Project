#include "Yard.h"

Yard::Yard() : sunScore(50) { // Starting with an initial sun score
    if (!scoreTexture.loadFromFile("../Images/sun.png")) {
        throw std::runtime_error("Failed to load sun score texture!");
    }
    scoreSprite.setTexture(scoreTexture);
    scoreSprite.setPosition(1000, -20); // Position the score card at top-left corner
}

void Yard::increaseSun(int amount) {
    sunScore += amount;
}

void Yard::decreaseSun(int amount) {
    if (sunScore >= amount) {
        sunScore -= amount;
    }
}

void Yard::updateScoreDisplay() {
    // This method can be used to dynamically update graphics or text as needed
}

void Yard::draw(sf::RenderWindow& window) {
    window.draw(scoreSprite);
    sf::RectangleShape scoreBox(sf::Vector2f(scoreSprite.getGlobalBounds().width, 30)); // Height is 30 pixels
    scoreBox.setPosition(scoreSprite.getPosition().x, scoreSprite.getPosition().y + scoreSprite.getGlobalBounds().height-23);
    scoreBox.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black
    scoreBox.setOutlineColor(sf::Color::White);
    scoreBox.setOutlineThickness(1.f);

    // Load and set font for text
    sf::Font font;
    if (!font.loadFromFile("../Images/fonts/serio.TTF")) {
        throw std::runtime_error("Failed to load font!");
    }
    sf::Text text(std::to_string(sunScore), font, 20);
    text.setPosition(scoreBox.getPosition().x + 10, scoreBox.getPosition().y + 5);
    text.setFillColor(sf::Color::White);

    // Draw the box and text on the window
    window.draw(scoreBox);
    window.draw(text);
}

int Yard::getSunScore() const {
    return sunScore;
}
