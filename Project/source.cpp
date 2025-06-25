#include <SFML/Graphics.hpp>
#include "Elements.h" 
#include "Plant.h"    
#include "Field.h"    
#include "Zombie.h"   
#include "PlantFactory.h"
#include "ZombieFactory.h" 
#include "PlantFactory.h"
#include "yard.h"
#include <iostream>
#include <ctime>

using namespace sf;
using namespace std;



Texture* createTexture(const string& filename) {
    Texture* texture = new Texture();
    if (!texture->loadFromFile(filename)) {
        cout << "Failed to load texture from: " << filename << endl;
        delete texture;
        return nullptr;
    }
    return texture;
}

const int MAX_PLANTS = 50;
Sunflower* sunflowers[MAX_PLANTS] = {};
Peashooter* peashooters[MAX_PLANTS] = {};
Repeater* repeaters[MAX_PLANTS] = {};
SnowPea* snowpeas[MAX_PLANTS] = {};
Wallnut* wallnuts[MAX_PLANTS] = {};
CherryBomb* cherrybombs[MAX_PLANTS] = {};
int sunflowerCount = 0, peashooterCount = 0, repeaterCount = 0, snowpeaCount = 0, wallnutCount = 0, cherrybombCount = 0;
Zombie** zombies;
int zombieCount = 0;


template<typename PlantType>
void handlePlantPlacement(RenderWindow& window, Vector2f mousePos, PlantType** plants, int& plantCount) {
    if (plantCount < MAX_PLANTS) {
        PlantType* newPlant = new PlantType();
        newPlant->setPosition(mousePos.x, mousePos.y);
        plants[plantCount++] = newPlant;
    }
}

template<typename PlantType>
void checkAndHandlePlantInteraction(RenderWindow& window, Event& event, Field& field, PlantType** plants, int& plantCount, bool& handled, const Vector2f& mousePos) {
    for (int i = 0; i < plantCount; ++i) {
        if (!plants[i]->isPlanted && plants[i]->displaySprite.getGlobalBounds().contains(mousePos)) {
            plants[i]->handleEvent(window, event, field);
            handled = true;
            break;
        }
    }
}

template<typename PlantType>
void propagateEventsToPlants(RenderWindow& window, Event& event, Field& field, PlantType* plants[], int plantCount) {
    for (int i = 0; i < plantCount; ++i) {
        plants[i]->handleEvent(window, event, field);
    }
}

template<typename PlantType>
void updateAndDrawPlants(RenderWindow& window, PlantType** plants, int plantCount) {
    for (int i = 0; i < plantCount; ++i) {
        plants[i]->update(zombies, zombieCount);  // Updated to include zombie interaction
        plants[i]->draw(window);
    }
}

const int MAX_ZOMBIES = 40;

void spawnZombies() {
    // Ensure initialization and dynamic management of zombie array
    if (zombieCount < MAX_ZOMBIES) {
        if (rand() % 2 == 0) zombies[zombieCount++] = ZombieFactory::createZombie("normal");
        if (rand() % 3 == 0) zombies[zombieCount++] = ZombieFactory::createZombie("dancing");
        if (rand() % 4 == 0) zombies[zombieCount++] = ZombieFactory::createZombie("flying");
        if (rand() % 5 == 0) zombies[zombieCount++] = ZombieFactory::createZombie("football");
    }
}

void updateAndDrawZombies(RenderWindow& window) {
    for (int i = 0; i < zombieCount; ++i) {
        zombies[i]->update();
        zombies[i]->draw(window);
        if (!zombies[i]->getisAlive()) { // Proper cleanup and management
            delete zombies[i];
            zombies[i] = zombies[--zombieCount];
            i--;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    RenderWindow window(VideoMode(1200, 700), "Zombie WarFrame");
    window.setFramerateLimit(60);
    Texture bgTexture = *createTexture("../Images/bgday.jpg");

    Sprite background(bgTexture);
    background.setPosition(0, 0);
    zombies = new Zombie * [MAX_ZOMBIES] {}; // Initialize the zombie array
    Sun s;
    Yard y;
    Clock zombieSpawnClock;
    Field field;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f mousePos = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
                bool handled = false;

                checkAndHandlePlantInteraction(window, event, field, peashooters, peashooterCount, handled, mousePos);
                checkAndHandlePlantInteraction(window, event, field, sunflowers, sunflowerCount, handled, mousePos);
                checkAndHandlePlantInteraction(window, event, field, repeaters, repeaterCount, handled, mousePos);
                checkAndHandlePlantInteraction(window, event, field, snowpeas, snowpeaCount, handled, mousePos);
                checkAndHandlePlantInteraction(window, event, field, cherrybombs, cherrybombCount, handled, mousePos);
                checkAndHandlePlantInteraction(window, event, field, wallnuts, wallnutCount, handled, mousePos);


                if (!handled) {
                    handlePlantPlacement(window, mousePos, peashooters, peashooterCount);
                    handlePlantPlacement(window, mousePos, sunflowers, sunflowerCount);
                    handlePlantPlacement(window, mousePos, repeaters, repeaterCount);
                    handlePlantPlacement(window, mousePos, snowpeas, snowpeaCount);
                    handlePlantPlacement(window, mousePos, wallnuts, wallnutCount);
                    handlePlantPlacement(window, mousePos, cherrybombs, cherrybombCount);
                }
            }
            else {
                // Propagate other events to all plants
                propagateEventsToPlants(window, event, field, sunflowers, sunflowerCount);
                propagateEventsToPlants(window, event, field, peashooters, peashooterCount);
                propagateEventsToPlants(window, event, field, repeaters, repeaterCount);
                propagateEventsToPlants(window, event, field, snowpeas, snowpeaCount);
                propagateEventsToPlants(window, event, field, wallnuts, wallnutCount);
                propagateEventsToPlants(window, event, field, cherrybombs, cherrybombCount);
            }
        }

        window.clear();
        window.draw(background);
        int time = rand() % 8 + 3;
        if (zombieSpawnClock.getElapsedTime().asSeconds() >= time) {
            spawnZombies();
            zombieSpawnClock.restart();
            time = rand() % 8 + 2;
        }

        updateAndDrawPlants(window, sunflowers, sunflowerCount);
        updateAndDrawPlants(window, peashooters, peashooterCount);
        updateAndDrawPlants(window, repeaters, repeaterCount);
        updateAndDrawPlants(window, snowpeas, snowpeaCount);
        updateAndDrawPlants(window, wallnuts, wallnutCount);
        updateAndDrawPlants(window, cherrybombs, cherrybombCount);
        updateAndDrawZombies(window);  // Draw zombies and update their state
        s.draw(window);
        s.update();
        y.draw(window);
          




        window.display();

    }

    // Clean up allocated plants
    for (int i = 0; i < sunflowerCount; ++i) delete sunflowers[i];
    for (int i = 0; i < peashooterCount; ++i) delete peashooters[i];
    for (int i = 0; i < repeaterCount; ++i) delete repeaters[i];
    for (int i = 0; i < snowpeaCount; ++i) delete snowpeas[i];
    for (int i = 0; i < wallnutCount; ++i) delete wallnuts[i];
    for (int i = 0; i < cherrybombCount; ++i) delete cherrybombs[i];
    for (int i = 0; i < zombieCount; ++i)delete zombies[i];

    return 0;
}