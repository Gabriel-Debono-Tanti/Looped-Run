#pragma once
#include "GameObject.hpp"

class PushBlock : public GameObject {
private:
    Vector2f velocity;
    float maxFallSpeed = 10.0f;
    float gravity = 0.6f;
public:

    PushBlock() {
        id = "PushBlock";
        scale = 2;
         isstatic = true;
    }

    void Init(sf::RenderWindow& window) override {
        SetTexture("Textures/cloudblock.png", IntRect({0, 0}, {16,9}));
        Animation idle = Animation(0, 1, 100);
        idle.getframe({16,9});
         ani.emplace("Idle", idle);
        collisionbox.setFillColor(Color::Transparent);
        
        sprite.setOrigin({sprite.getGlobalBounds().size.x/2, sprite.getGlobalBounds().size.y/2});
        collisionbox.setOrigin({collisionbox.getGlobalBounds().size.x/2, collisionbox.getGlobalBounds().size.y/2});
       Setanimation("Idle");
    }

    void Update(sf::RenderWindow& window) override {
        RunAnimation();
        

   collisionbox.setSize(Vector2f({sprite.getGlobalBounds().size.x, sprite.getGlobalBounds().size.y}));
       collisionbox.setPosition({sprite.getPosition().x , sprite.getPosition().y});
        
         velocity.y += gravity;
        if (velocity.y > maxFallSpeed)
            velocity.y = maxFallSpeed;

        sprite.move({velocity.x, velocity.y});
    }

    void Render(sf::RenderWindow& window) override {
        window.draw(sprite);
        window.draw(collisionbox);
    }

    // Override collision detection logic
     bool isCollidingWith(const GameObject& other) override {
       
        if (collisionbox.getGlobalBounds().findIntersection(other.collisionbox.getGlobalBounds()).has_value()) {
         
             if(other.isstatic){
              
             sf::FloatRect spriteBounds = collisionbox.getGlobalBounds();
       
            sf::FloatRect wallBounds = other.collisionbox.getGlobalBounds();
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
        
      
        // Add more conditions for different id checks as needed
        return false;
   
    }
      void VectorUse( const vector<GameObject*>& gameObjects)override{
        
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
                        
                    } else {
                        sprite.move({0, intersection.size.y});
                        velocity.y = 0;
                    }
                }
            }
        }
    }
};