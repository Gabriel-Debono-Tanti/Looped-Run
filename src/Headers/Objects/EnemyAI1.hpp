#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include <optional>
#include <math.h>
using namespace sf;
using namespace std;

class EnemyAI1 : public Enemy
{
private:
    optional<sf::Vector2f> target;
    float movementspeed = 2;
    float range = 500;
    float distanceToTarget;
    bool allowMove = false;
public:
void Init(sf::RenderWindow& window) override {
        SetTexture("Textures/1.png",IntRect({0, 0}, {14,10}));
        Animation idle = Animation(0, 1, 100);
        idle.getframe({14,10});
         ani.emplace("Idle", idle);
        setPosition({200, 100});
        scale =2;
    }
    void HandleWallCollisions(vector<Wall>& levelwalls) override{
        walls = levelwalls;
         sf::FloatRect spriteBounds = collisionbox.getGlobalBounds();
        for (const Wall& wall : walls) {
            sf::FloatRect wallBounds = wall.Wallbox.getGlobalBounds();
            if (spriteBounds.findIntersection(wallBounds)) {
                FloatRect overlap = spriteBounds.findIntersection(wallBounds).value();
                
                
                if (overlap.size.x < overlap.size.y) {
                    if (spriteBounds.position.x < wallBounds.position.x) {
                        sprite.setPosition({sprite.getPosition().x - overlap.size.x + 0.1f, sprite.getPosition().y});
                    } else {
                        sprite.setPosition({sprite.getPosition().x + overlap.size.x -0.1f, sprite.getPosition().y});    
                    }
                } else {
                    if (spriteBounds.position.y < wallBounds.position.y) {
                        sprite.setPosition({sprite.getPosition().x, sprite.getPosition().y - overlap.size.y});
                    } else {
                        sprite.setPosition({sprite.getPosition().x, sprite.getPosition().y + overlap.size.y});
                    }
                }
            }
        }
   }
    void Update(sf::RenderWindow& window) override {
        Setanimation("Idle");
        RunAnimation();
      
        collisionbox.setSize(Vector2f({sprite.getGlobalBounds().size.x, sprite.getGlobalBounds().size.y - 10}));
        collisionbox.setPosition(Vector2f({sprite.getPosition().x, sprite.getPosition().y + (sprite.getGlobalBounds().size.y * 0.25f)}));
        
        
        if (target) {
            sf::Vector2f vectorToTarget = target.value() - sprite.getPosition();
            float distanceToTarget = sqrt(vectorToTarget.x * vectorToTarget.x + vectorToTarget.y * vectorToTarget.y);
    
            if (distanceToTarget < movementspeed) {
                sprite.move(vectorToTarget);
            } else {
                sf::Vector2f movementDirection = vectorToTarget / distanceToTarget;
                sprite.move(movementDirection * movementspeed);
            }
    
            flip = (vectorToTarget.x < 0);
        }
    }
    void Render(sf::RenderWindow& window) override {
        window.draw(sprite);
        window.draw(collisionbox);
    }

    
    bool isCollidingWith(const GameObject& other) override {
       
    if (sprite.getGlobalBounds().findIntersection(other.sprite.getGlobalBounds())) {
            if (id == "Enemy" && other.id == "Projectile") {
               std::cout << "Collision detected between " << id << " and " << other.id << "!" << std::endl;
                return true;
            }
        }
       
       return false;
    }
    void VectorUse(const vector<GameObject*>& gameObjects)override{
        target.reset(); // Reset target
        float closestDistance = range;

        for (auto* obj : gameObjects) {
            if (obj->id == "Player") { // Filter for players
                sf::Vector2f vectorToPlayer = obj->getPosition() - sprite.getPosition();
                float distanceToPlayer = sqrt(vectorToPlayer.x * vectorToPlayer.x + vectorToPlayer.y * vectorToPlayer.y);

                if (distanceToPlayer < closestDistance) {
                    closestDistance = distanceToPlayer;
                    target = obj->getPosition(); // Update the closest target
                }
            }
        }
    }
};
