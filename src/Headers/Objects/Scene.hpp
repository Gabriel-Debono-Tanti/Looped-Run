#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include <optional>
using namespace std;
class Scene
{
private:
    
public:
    vector<GameObject*> gameObjects;
    virtual void Init(sf::RenderWindow& window) = 0;
    virtual void Update(sf::RenderWindow& window) = 0;
    virtual void Events(sf::RenderWindow& window, const optional<Event>& event) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    static int index;
    static bool cs;
    virtual void checkCollisions() {
    // Loop through each pair of GameObjects in the vector
    for (size_t i = 0; i < gameObjects.size(); ++i) {
        
        for (size_t j = i + 1; j < gameObjects.size(); ++j) {
        
            // Call the overridden isCollidingWith method
            if (gameObjects[i]->isCollidingWith(*gameObjects[j])) {
                // Handle collision between gameObjects[i] and gameObjects[j]
                //cout << "Collision detected between " << gameObjects[i]->id
                     //<< " and " << gameObjects[j]->id << "!" << endl;
            }
        }
    }
}
};

int Scene::index = 0;
bool Scene::cs = false;