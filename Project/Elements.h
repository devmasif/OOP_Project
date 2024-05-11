#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace sf;




// Base class for all game elements
class Elements {
protected:
    sf::Vector2f position;
    sf::Sprite sprite;

public:
    virtual void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
        sprite.setPosition(position);
    }

    virtual sf::Vector2f getPosition() const {
        return position;
    }

    virtual void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    virtual void update() = 0;  // Pure virtual for updates per frame
    virtual void action() = 0;  // Pure virtual for specific element action
};



class Sun : public Elements {
private:
    bool falling;
    int speed = 1;
    sf::Texture texture;
    sf::Clock sunClock, waitClock; // Additional clock for waiting
    bool waiting = false; // State to handle waiting at the score position
    int score = 0;

public:
    Sun(bool fall = true) : falling(fall) {
        if (!texture.loadFromFile("../Images/sun.png")) {
            cout << "Failed to load sun texture" << endl;
        }
        sprite.setTexture(texture);
        resetPosition(); // Set initial position randomly
    }

    void resetPosition() {
        int x = 200 + rand() % 400; // Random x between 200 and 600
        setPosition(x, 0); // Set position at top with random x
        falling = true; // Sun starts falling
        waiting = false; // Not waiting
        waitClock.restart(); // Restart wait clock when position is reset
    }

    void update() override {
        if (waiting) {
            if (waitClock.getElapsedTime().asSeconds() > 10) {
                resetPosition(); // Reset position after waiting
            }
        }
        else if (falling) {
            if (sunClock.getElapsedTime().asMilliseconds() > 50) {
                position.y += speed;
                sprite.setPosition(position);
                sunClock.restart();
                score += 25;
            }

            if (position.y > 120) { // When sun reaches the limit
                position.x = 5; // Move to top-left corner
                position.y = 5;
                sprite.setPosition(position);
                falling = false;
                waiting = true;
                waitClock.restart(); // Start wait clock
            }
        }
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(sprite);
    }

    void action() {

    }

};



class Field {
private:
    vector<sf::FloatRect> plantableBoxes;
    sf::Vector2f boxSize;

public:
    Field() {
        boxSize = sf::Vector2f(75, 100); 
        initializeField();
    }

    void initializeField() {
        for (int x = 250; x <= 980 ; x += 80) { // Adjust based on your field dimensions
            for (int y = 80; y <= 570; y += 100) {
                plantableBoxes.push_back(sf::FloatRect(x, y, boxSize.x, boxSize.y));
            }
        }
    }

    bool isPlantableArea(const sf::Vector2f& position) {
        for (auto& box : plantableBoxes) {
            if (box.contains(position)) {
                return true;
            }
        }
        return false;
    }

    sf::Vector2f snapToBox(const sf::Vector2f& position) {
        for (auto& box : plantableBoxes) {
            if (box.contains(position)) {
                return sf::Vector2f(box.left, box.top);
            }
        }
        return position; // If not in any box, return original position (or handle as error)
    }
};



class Plant : public Elements {
protected:
    sf::Texture texture;

public:
    virtual void update() = 0;  // Pure virtual for specific plant updates
    virtual void action() = 0;  // Pure virtual for plant-specific actions
};

class Sunflower : public Plant {
public:
    Texture displayTexture, dragTexture;
    Sprite displaySprite, dragSprite;
    bool isDragging, isPlanted;
    Vector2f dragOffset;
    Clock animationClock, generationClock;

    int num;
    Clock textureClock;

    Sunflower() :num(0) {
        loadTextures();
        setupSprites();
    }

    void loadTextures() {
        if (!displayTexture.loadFromFile("../Images/sunflower2.png")) {
            cout << "Failed to load display image!" << endl;
        }
        if (!dragTexture.loadFromFile("../assets/plants/sunFlower/sunFlower_0.png")) {
            cout << "Failed to load drag image!" << endl;
        }
    }

    void setupSprites() {
        displaySprite.setTexture(displayTexture);
        displaySprite.setPosition(0,140); // Original position
        displaySprite.setScale(1.f, 1.f);

        dragSprite.setTexture(dragTexture);
        dragSprite.setScale(1.f, 1.f);
        dragSprite.setColor(Color(255, 255, 255, 0)); // Initially make dragSprite invisible

        isDragging = false;
        isPlanted = false;
    }

    void handleEvent(RenderWindow& window, Event& event, Field& field) {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
            if (displaySprite.getGlobalBounds().contains(mousePos) ) {
                isDragging = true;
                dragOffset = mousePos - displaySprite.getPosition();
                dragSprite.setPosition(displaySprite.getPosition());
                dragSprite.setColor(Color(255, 255, 255, 255)); // Make dragSprite visible
            }
        }

        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            if (isDragging) {
                Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                Vector2f snapPos = field.snapToBox(mousePos - dragOffset);
                if (field.isPlantableArea(snapPos)) {
                    dragSprite.setPosition(snapPos);
                    isPlanted = true;
                }
                else {
                    dragSprite.setColor(Color(255, 255, 255, 0)); // Make invisible if not plantable
                }
                isDragging = false;
            }
        }

        if (event.type == Event::MouseMoved && isDragging) {
            Vector2f mousePos = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
            dragSprite.setPosition(mousePos - dragOffset);
        }
    }


    void update() override {
       
        // Check if 1 millisecond has passed since the last texture change
        if (textureClock.getElapsedTime().asMilliseconds() >= 50) {
            textureClock.restart(); // Restart the clock for the next millisecond
            num = (num + 1) % 17; // Increment num and reset to 0 when it reaches 16
            //cout << "n" <<num << endl;
            // Construct the filename for the new texture
            string sunflower = "../assets/plants/sunFlower/sunFlower_" + to_string(num) + ".png";

            // Load the new texture
            if (!dragTexture.loadFromFile(sunflower)) {
                cout << "Failed to load texture: " << sunflower << endl;
            }
        }
    }

    void draw(RenderWindow& window) override {
        window.draw(displaySprite);
        if (isPlanted || dragSprite.getColor().a != 0) {
            window.draw(dragSprite);
        }
    }

    void action() override {
        Sun s();
    }
};


class Peashooter : public Plant {
public:
    Texture displayTexture, dragTexture;
    Sprite displaySprite, dragSprite;
    bool isDragging, isPlanted;
    Vector2f dragOffset;
    Clock animationClock, generationClock;

    int num;
    Clock textureClock;

public:
    Peashooter() : num(0), isDragging(false), isPlanted(false) {
        loadTextures();
        setupSprites();
    }

    void loadTextures() {
        if (!displayTexture.loadFromFile("../Images/peashooter.png")) {
            cout << "Failed to load display image!" << endl;
        }
        if (!dragTexture.loadFromFile("../assets/plants/Peashooter/Peashooter_0.png")) {
            cout << "Failed to load drag image!" << endl;
        }
    }

    void setupSprites() {
        displaySprite.setTexture(displayTexture);
        displaySprite.setPosition(0, 205); // Original position
        displaySprite.setScale(1.f, 1.f);

        dragSprite.setTexture(dragTexture);
        dragSprite.setScale(1.f, 1.f);
        dragSprite.setColor(Color(255, 255, 255, 0)); // Initially make dragSprite invisible

        isDragging = false;
        isPlanted = false;
    }

    void handleEvent(RenderWindow& window, Event& event, Field& field) {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
            if (displaySprite.getGlobalBounds().contains(mousePos)) {
                isDragging = true;
                dragOffset = mousePos - displaySprite.getPosition();
                dragSprite.setPosition(displaySprite.getPosition());
                dragSprite.setColor(Color(255, 255, 255, 255)); // Make dragSprite visible
            }
        }

        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            if (isDragging) {
                Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                Vector2f snapPos = field.snapToBox(mousePos - dragOffset);
                if (field.isPlantableArea(snapPos)) {
                    dragSprite.setPosition(snapPos);
                    isPlanted = true;
                }
                else {
                    dragSprite.setColor(Color(255, 255, 255, 0)); // Make invisible if not plantable
                }
                isDragging = false;
            }
        }

        if (event.type == Event::MouseMoved && isDragging) {
            Vector2f mousePos = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
            dragSprite.setPosition(mousePos - dragOffset);
        }
    }

    void update() override {
        if (textureClock.getElapsedTime().asMilliseconds() >= 50) {
            textureClock.restart(); // Restart the clock for the next millisecond
            num = (num + 1) % 13; // Increment num and reset to 0 when it reaches 16
            string peashooter = "../assets/plants/Peashooter/Peashooter_" + to_string(num) + ".png";
            if (!dragTexture.loadFromFile(peashooter)) {
                cout << "Failed to load texture: " << peashooter << endl;
            }
        }
    }

    void draw(RenderWindow& window) override {
        window.draw(displaySprite);
        if (isPlanted || dragSprite.getColor().a != 0) {
            window.draw(dragSprite);
        }
    }

    void action() override {
        // Peashooter-specific action
    }
};


class PlantFactory {
public:
    static Plant* createPlant(const string& type) {
        if (type == "Peashooter") return new Peashooter();
        if (type == "Sunflower") return new Sunflower();
        // Add more plant types as necessary
        return nullptr;
    }
};





#endif
