#include <SFML/Graphics.hpp>
#include "Elements.h"
using namespace sf;
using namespace std;




struct Coordinates {
    int x;
    int y;
};

Sprite createSprite(const string& filename) {
    Texture* texture = new Texture();
    if (!texture->loadFromFile(filename)) {
        cout << "Failed to load texture from: " << filename << endl;
    }
    Sprite sprite;
    sprite.setTexture(*texture);
    return sprite;
}

void createBackground(RenderWindow& window) {
    Sprite s_map = createSprite("../Images/bgday.jpg");
    s_map.setPosition(0, 0);
    window.draw(s_map);
}

void createMap(RenderWindow& window) {
    Sprite s_map = createSprite("../Images/grid.png");
    s_map.setPosition(300, 160);
    window.draw(s_map);
}

const int MAX_PLANTS = 50;
Sunflower* sunflowers[MAX_PLANTS ] = {};  // Array to store sunflowers
Peashooter* peashooters[MAX_PLANTS] = {}; // Array to store peashooters
int sunflowerCount = 0;
int peashooterCount = 0;




int main() {
    RenderWindow window(VideoMode(1200, 700), "Zombie WarFrame");
    window.setFramerateLimit(60);

    // Setting the window icon
    Image icon;
    if (!icon.loadFromFile("../Images/icon.png")) {
        cout << "Failed to load game icon." << endl;
        return 1;
    }
    window.setIcon(32, 32, icon.getPixelsPtr());

    Texture bgTexture;
    if (!bgTexture.loadFromFile("../Images/bgday.jpg")) {
        cout << "Failed to load background texture." << endl;
    }
    Sprite background(bgTexture);
    background.setPosition(0, 0);

    // Main game loop
    while (window.isOpen()) {
        Event event;
        Field field;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

                // Handling plant selection and dragging
                bool handled = false;
                // Handling Sunflowers
                for (int i = 0; i < sunflowerCount; ++i) {
                    if (sunflowers[i]->displaySprite.getGlobalBounds().contains(mousePos) && !sunflowers[i]->isPlanted) {
                        sunflowers[i]->handleEvent(window, event, field);
                        handled = true;
                        break;
                    }
                }
                // Handling Peashooters
                for (int i = 0; i < peashooterCount; ++i) {
                    if (peashooters[i]->displaySprite.getGlobalBounds().contains(mousePos) && !peashooters[i]->isPlanted) {
                        peashooters[i]->handleEvent(window, event, field);
                        handled = true;
                        break;
                    }
                }

                // Add new plants if needed
                if (!handled && sunflowerCount < MAX_PLANTS) {
                    sunflowers[sunflowerCount] = new Sunflower();
                    sunflowers[sunflowerCount]->setPosition(mousePos.x, mousePos.y);
                    sunflowerCount++;
                }
                if (!handled && peashooterCount < MAX_PLANTS) {
                    peashooters[peashooterCount] = new Peashooter();
                    peashooters[peashooterCount]->setPosition(mousePos.x, mousePos.y);
                    peashooterCount++;
                }
            }
            else {
                // Propagate other events to all plants
                for (int i = 0; i < sunflowerCount; ++i) {
                    sunflowers[i]->handleEvent(window, event, field);
                }
                for (int i = 0; i < peashooterCount; ++i) {
                    peashooters[i]->handleEvent(window, event, field);
                }
            }
        }

        window.clear();
        window.draw(background);

        // Draw and update all plants
        for (int i = 0; i < sunflowerCount; ++i) {
            sunflowers[i]->draw(window);
            sunflowers[i]->update();
        }
        for (int i = 0; i < peashooterCount; ++i) {
            peashooters[i]->draw(window);
            peashooters[i]->update();
        }

        window.display();
    }

    // Clean up allocated plants
    for (int i = 0; i < sunflowerCount; ++i) {
        delete sunflowers[i];
    }
    for (int i = 0; i < peashooterCount; ++i) {
        delete peashooters[i];
    }

    return 0;
}

       
