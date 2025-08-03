#pragma once
#include "GameObject.hpp"

using namespace std;
using namespace sf;

class Enemy : public GameObject
{
public:
    Enemy() {
        id = "Enemy";
    }

    void Init(sf::RenderWindow& window) override {
        SetTexture("Textures/1.png", IntRect({0, 0}, {14,10}));
        setPosition({200, 100});
        scale = 2;

        
    }

    void Update(sf::RenderWindow& window) override {
      //   collisionbox.setSize({sprite.getGlobalBounds().size.x,sprite.getGlobalBounds().size.y-10});
      //  collisionbox.setPosition({sprite.getPosition().x, sprite.getPosition().y + (sprite.getGlobalBounds().size.y*.25f)});
    }

    void Render(sf::RenderWindow& window) override {
        window.draw(sprite);
        window.draw(collisionbox);
    }

    // Override collision detection logic
    bool isCollidingWith(const GameObject& other) override {
       
    if (sprite.getGlobalBounds().findIntersection(other.sprite.getGlobalBounds())) {
            if (id == "Enemy" && other.id == "Projectile") {
               std::cout << "Collision detected between " << id << " and " << other.id << "!" << std::endl;
                return true;
            }
        }
        // Add more conditions for different id checks as needed
       return false;
    }
    void VectorUse( const vector<GameObject*>& gameObjects)override{
        
    }
    void HandleWallCollisions(vector<Wall>& levelwalls) override{
       
   }
   
};


