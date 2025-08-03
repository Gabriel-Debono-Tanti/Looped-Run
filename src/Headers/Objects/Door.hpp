#pragma once
#include "GameObject.hpp"

class Door : public GameObject {
private:
   
   float openpos, closepos;
public:
int  dc;
bool  open =false;
    Door( int code, Vector2f position) {
        id = "Door";
        scale = 2;
       setPosition(position);
        
        dc= code;
        isstatic = true;
    }

    void Init(sf::RenderWindow& window) override {
      
     
        collisionbox.setFillColor(Color::Transparent);
         
        
        
         
         openpos = sprite.getPosition().y -60;
        closepos = sprite.getPosition().y; 
        SetTexture("Textures/door.png", IntRect(Vector2i(0,0), Vector2i(10, 32)));
       
        Animation idle = Animation(0, 1, 100); 
        idle.getframe(sprite.getTextureRect().size);
         ani.emplace("Idle", idle);
         Setanimation("Idle");
       
    }

    void Update(sf::RenderWindow& window) override {
        
        RunAnimation();
       
          collisionbox.setSize({sprite.getGlobalBounds().size.x,sprite.getGlobalBounds().size.y});
        collisionbox.setPosition({sprite.getPosition().x, sprite.getPosition().y});
        
        float newpos = sprite.getPosition().y;
        if (open) {
            if (newpos > openpos) {
                newpos -= 1;
            }
        } else {
            if (newpos < closepos) {
                newpos += 1;
            }
        }
        sprite.setPosition({sprite.getPosition().x, newpos});
    
    }

    void Render(sf::RenderWindow& window) override {
        window.draw(sprite);
        window.draw(collisionbox);
    }

    // Override collision detection logic
    bool isCollidingWith(const GameObject& other) override {
       
        // Add more conditions for different id checks as needed
        return false;
   // }
    }
      void VectorUse( const vector<GameObject*>& gameObjects)override{
        
      }
   
};