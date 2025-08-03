#pragma once
#include "GameObject.hpp"

class Player : public GameObject {
private:
Vector2f velocity;
    float gravity = 0.6f;
    float jumpForce = -15.0f;
    float dashForce = 10.0f;
    float maxFallSpeed = 10.0f;
    float speed = 4;
    bool canJump = true;
   
    float dashtimer = .5f;   
    float health = 100;
    bool record = true;
public:
vector<Vector2f> recording;
    Player() {
        id = "Player";
        scale = 2;
        isstatic = true;
    }

    void Init(sf::RenderWindow& window) override {
         SetTexture("Textures/entitysheet.png", IntRect({0, 0}, {14,10}));
        Animation idle = Animation(0, 7, 100);
        idle.getframe({14, 24});
         ani.emplace("Idle", idle);
         Animation move = Animation(1, 7, 100);
        move.getframe({14, 24});
         ani.emplace("Move", move);
         Animation jump = Animation(2, 1, 100);
        jump.getframe({14, 24});
         ani.emplace("Jump", jump);

        collisionbox.setFillColor(Color::Transparent);
       
        sprite.setOrigin({sprite.getGlobalBounds().size.x/2, sprite.getGlobalBounds().size.y/2});
        collisionbox.setOrigin({collisionbox.getGlobalBounds().size.x/2, collisionbox.getGlobalBounds().size.y/2});
        
       
    }

    void Update(sf::RenderWindow& window) override {
    
    //

    // Horizontal input
    if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
        sprite.move({-speed, 0});
        Setanimation("Move");
        flip = true;
    } else if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
        sprite.move({speed, 0});
        Setanimation("Move");
        flip = false;
    }else{
        Setanimation("Idle");
    }
    if (Keyboard::isKeyPressed(Keyboard::Key::Space) && canJump) {
        velocity.y = jumpForce;
        canJump = false;
        Setanimation("Jump");
    }

    // Gravity
    velocity.y += gravity;
    if (velocity.y > maxFallSpeed)
        velocity.y = maxFallSpeed;

    // Apply vertical movement
    sprite.move({0, velocity.y});

    // Update collisionbox size and position AFTER movement
      collisionbox.setSize(Vector2f({sprite.getGlobalBounds().size.x, sprite.getGlobalBounds().size.y}));
       collisionbox.setPosition({sprite.getPosition().x , sprite.getPosition().y});

    // Record movement
    RunAnimation();
    recording.push_back(sprite.getPosition());
}

    void HandleWallCollisions(vector<Wall>& levelwalls) override{
        walls = levelwalls;
        for (const Wall& wall : walls) {
            FloatRect playerBounds = sprite.getGlobalBounds();
            FloatRect wallBounds = wall.Wallbox.getGlobalBounds();

            
            if (playerBounds.findIntersection(wallBounds)) {
                FloatRect intersection = playerBounds.findIntersection(wallBounds).value();
                
                if (intersection.size.x < intersection.size.y) {
                    if (playerBounds.position.x < wallBounds.position.x) {
                        sprite.move({-intersection.size.x, 0});
                    } else {
                        sprite.move({intersection.size.x, 0});
                    }
                } else {
                    if (playerBounds.position.y < wallBounds.position.y) {
                        sprite.move({0, -intersection.size.y});
                        velocity.y = 0;
                        canJump = true;
                       dashtimer = .03f;
                    } else {
                        if(!wall.issemistatic){
                            sprite.move({0, intersection.size.y});
                        velocity.y = 0;
                        }
                        
                    }
                }
                
            }
        }
   }
    void Render(sf::RenderWindow& window) override {
        window.draw(sprite);
        window.draw(collisionbox);
    }

    // Override collision detection logic
   bool isCollidingWith(const GameObject& other) override {
    if (collisionbox.getGlobalBounds().findIntersection(other.collisionbox.getGlobalBounds()).has_value()) {
        if (other.id == "Enemy") {
            //std::cout << "Collision detected between " << id << " and " << other.id << "!" << std::endl;
        }

        if (other.isstatic && other.id != "Enemy") {
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

        return true;
    }

    return false;
}
      void VectorUse( const vector<GameObject*>& gameObjects)override{
        
      }
};