#pragma once
#include "GameObject.hpp"
class Recording : public GameObject
{
private:
   
public:
 int currentIndex = 0;
bool playbackFinished = false;
    vector<Vector2f> prec;
    Recording(/* args */);
    void Init(RenderWindow& window) override{
         SetTexture("Textures/entitysheet.png", IntRect({0, 0}, {14,10}));
        Animation idle = Animation(0, 7, 100);
        idle.getframe({14, 24});
         ani.emplace("Idle", idle);
         Animation move = Animation(1, 7, 100);
        move.getframe({14, 24});
         ani.emplace("Move", move);
         
        collisionbox.setFillColor(Color::Transparent);
        setPosition({500, 900});
        sprite.setOrigin({sprite.getGlobalBounds().size.x/2, sprite.getGlobalBounds().size.y/2});
        collisionbox.setOrigin({collisionbox.getGlobalBounds().size.x/2, collisionbox.getGlobalBounds().size.y/2});
        isstatic = true;
        sprite.setColor(Color(255, 255, 255, 128));
    }
    void Update(RenderWindow& window) override{
          
        

      collisionbox.setSize(Vector2f({sprite.getGlobalBounds().size.x, sprite.getGlobalBounds().size.y}));
       collisionbox.setPosition({sprite.getPosition().x , sprite.getPosition().y});
        if (!playbackFinished && currentIndex < prec.size()) {
        sprite.setPosition(prec[currentIndex]);
        float diff = prec[currentIndex].x - prec[currentIndex-1].x;
        if(diff < 0){
            flip = true;
            Setanimation("Move");
        }else if(diff > 0){
             flip = false;
            Setanimation("Move");
        }else{
            Setanimation("Idle");
        }
        currentIndex++;
    } else {
        playbackFinished = true;
    }
    RunAnimation();
    }
    void Render(RenderWindow& window) override{
          window.draw(sprite);
        window.draw(collisionbox);
    }
    void VectorUse(const vector<GameObject*>& gameObjectsr) override{
        
    }
    bool isCollidingWith(const GameObject& other) override {
    if (collisionbox.getGlobalBounds().findIntersection(other.collisionbox.getGlobalBounds()).has_value()) {
     

        if (other.isstatic && other.id != id) {
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
                       
                       
                    } else {
                        sprite.move({0, intersection.size.y});
                        
                    }
                }
            }
        }

        return true;
    }

    return false;
}
    void HandleWallCollisions(vector<Wall>& levelwalls)override{
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
                        
                      
                    } else {
                        if(!wall.issemistatic){
                            sprite.move({0, intersection.size.y});
                        
                        }
                        
                    }
                }
                
            }
        }
   }
    ~Recording();
};

Recording::Recording(/* args */)
{
      id = "Recording";
      scale =2;
}

Recording::~Recording()
{
}
