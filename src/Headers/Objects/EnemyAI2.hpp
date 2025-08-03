#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include <optional>
#include <math.h>
using namespace sf;
using namespace std;

class EnemyAI2 : public Enemy
{
private:
    optional<sf::Vector2f> target;
    float movementspeed = 2;
    float range = 500;
    float distanceToTarget;
    bool allowMove = false;

    Vector2f velocity;
    float gravity = 0.6f;
    float jumpForce = -15.0f;
    float dashForce = 15.0f;
    float maxFallSpeed = 10.0f;
    bool canJump = true;

    FloatRect ltrig, rtrig;

public:
void Init(sf::RenderWindow& window) override {
        SetTexture("Textures/enemysheet.png", IntRect({0, 0}, {14,10}));
         Animation idle = Animation(0, 7, 100);
        idle.getframe({14, 24});
         ani.emplace("Idle", idle);
         Animation move = Animation(1, 7, 100);
        move.getframe({14, 24});
         ani.emplace("Move", move);
         Animation jump = Animation(2, 1, 100);
        jump.getframe({14, 24});
         ani.emplace("Jump", jump);
       id = "Enemy";
        scale =2;
        isstatic = true;
       
    }

    void Update(sf::RenderWindow& window) override {
        
        

        Vector2f pos = sprite.getPosition();
Vector2f spriteSize = {sprite.getGlobalBounds().size.x, sprite.getGlobalBounds().size.y};

// Vertical strip beside the enemy
float triggerWidth = 5.0f; // Thin slice extending sideways
float triggerHeight = spriteSize.y * 0.5f; // Half the enemy’s height

// Place triggers halfway down the sides
ltrig = FloatRect(
    {pos.x - triggerWidth,
    pos.y + spriteSize.y * 0.25f},
    {triggerWidth,
    triggerHeight}
);

rtrig = FloatRect(
    {pos.x + spriteSize.x,
    pos.y + spriteSize.y * 0.25f},
    {triggerWidth,
    triggerHeight}
);

        
        collisionbox.setSize(Vector2f({sprite.getGlobalBounds().size.x, sprite.getGlobalBounds().size.y - 10}));
        collisionbox.setPosition(Vector2f({sprite.getPosition().x, sprite.getPosition().y + (sprite.getGlobalBounds().size.y * 0.25f)}));
        
        // ✅ Check if target exists before using it
        if (target) {
            sf::Vector2f vectorToTarget = target.value() - sprite.getPosition();
            float distanceToTarget = sqrt(vectorToTarget.x * vectorToTarget.x + vectorToTarget.y * vectorToTarget.y);
    
            if (distanceToTarget < movementspeed) {
                sprite.move({vectorToTarget.x, 0});
            } else {
                sf::Vector2f movementDirection = vectorToTarget / distanceToTarget;
                sprite.move({movementDirection.x * movementspeed, 0});
            }
            if(vectorToTarget.x < vectorToTarget.y){
               Setanimation("Idle"); 
            }else{
                Setanimation("Move");
            }
            flip = (vectorToTarget.x < 0);
            
        }else{
            Setanimation("Idle");
        }
         velocity.y += gravity;
        if (velocity.y > maxFallSpeed)
            velocity.y = maxFallSpeed;
        
            RunAnimation();
        sprite.move({velocity.x, velocity.y});
    }
    void Render(sf::RenderWindow& window) override {
        window.draw(sprite);
        //window.draw(collisionbox);
    }

    
    bool isCollidingWith(const GameObject& other) override {
       
    if (sprite.getGlobalBounds().findIntersection(other.sprite.getGlobalBounds())) {
            if (other.isstatic) {
            sf::FloatRect playerBounds = collisionbox.getGlobalBounds();
            sf::FloatRect otherBounds = other.collisionbox.getGlobalBounds();
            auto intersectionOpt = playerBounds.findIntersection(otherBounds);

            if (intersectionOpt) {
                FloatRect intersection = intersectionOpt.value();

                if (intersection.size.x < intersection.size.y) {
                    // Horizontal resolution
                    if (playerBounds.position.x < otherBounds.position.x) {
                        sprite.move({-intersection.size.x, 0});
                    } else {
                        sprite.move({intersection.size.x, 0});
                    }
                } else {
                    // Vertical resolution
                    if (playerBounds.position.y < otherBounds.position.y) {
                        sprite.move({0, -intersection.size.y});
                        velocity.y = 0;
                        canJump = true;
                    } else {
                        sprite.move({0, intersection.size.y});
                        velocity.y = 0;
                    }
                }
            }
        }
        }
       
       return false;
    }
    void HandleWallCollisions(vector<Wall>& levelwalls) override{
        walls = levelwalls;
        for (const Wall& wall : walls) {
            FloatRect enemyBounds = sprite.getGlobalBounds();
            FloatRect wallBounds = wall.Wallbox.getGlobalBounds();

            auto intersectionOpt = enemyBounds.findIntersection(wallBounds);
            if (intersectionOpt) {
                FloatRect intersection = intersectionOpt.value();

                if (intersection.size.x < intersection.size.y) {
                    // Horizontal collision
                    if (enemyBounds.position.x < wallBounds.position.x) {
                        sprite.move({-intersection.size.x, 0});
                    } else {
                        sprite.move({intersection.size.x, 0});
                    }
                } else {
                    // Vertical collision
                    if (enemyBounds.position.y < wallBounds.position.y) {
                        sprite.move({0, -intersection.size.y});
                        velocity.y = 0;
                        canJump = true;
                    } else {
                        sprite.move({0, intersection.size.y});
                        velocity.y = 0;
                    }
                }
            }

            // Trigger-based jump
            if (ltrig.findIntersection(wallBounds) || rtrig.findIntersection(wallBounds)) {
                if (canJump) {
                    velocity.y = jumpForce;
                    Setanimation("Jump");
                    canJump = false;
                }
            }
        }
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
