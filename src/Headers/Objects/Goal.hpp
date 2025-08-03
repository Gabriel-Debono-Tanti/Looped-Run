#pragma once
#include "GameObject.hpp"
#include "Button.hpp"

class Goal : public GameObject {
private:
    Button nextLevel = Button("Textures/UI/NextLevel.png", 30, 30);
    Button tomenu = Button("Textures/UI/ToMain.png", 30, 30);
    
    Font font = Font("Fonts/font1.ttf");
    Text text = Text(font);
public:bool finished = false;
    Goal() {
        id = "Goal";
        scale = 2.5f;
       
    }

    void Init(RenderWindow& window) override {
        nextLevel.Scale(Vector2f(3, 3));
        tomenu.Scale({3,3});
        nextLevel.SetPosition({1800, 900}); // Set to a visible position
        tomenu.SetPosition({40, 30});
        SetTexture("Textures/goal.png", IntRect({0, 0}, {16, 19}));
        Animation idle(0, 1, 100);
        idle.getframe({16, 19});
        ani.emplace("Idle", idle);
        text.setString("Level Completed!");
        text.setCharacterSize(48);
        text.setPosition({750, 40});
        text.setFillColor(sf::Color::Black);
        Setanimation("Idle");

       
       collisionbox.setFillColor(Color::Transparent);
       sprite.setOrigin({sprite.getGlobalBounds().size.x/2, sprite.getGlobalBounds().size.y/2});
        collisionbox.setOrigin({collisionbox.getGlobalBounds().size.x/2, collisionbox.getGlobalBounds().size.y/2});

       
    }

    void Update(RenderWindow& window) override {
        RunAnimation();

        collisionbox.setSize({ sprite.getGlobalBounds().size.x, sprite.getGlobalBounds().size.y });
        collisionbox.setPosition(sprite.getPosition());
    }

    void Next(Music& music,int& index, bool& cs, RenderWindow& window) {
        Vector2i mousePos = Mouse::getPosition(window);
        Vector2f mouseWorld = window.mapPixelToCoords(mousePos);
        if(index == 9){
            text.setString("You've Beaten The Game!");
        }
        if (nextLevel.contains(mouseWorld) && finished and index <= 8) {
            if (Mouse::isButtonPressed(Mouse::Button::Left)) {
                index += 1;
                music.stop();
                cs = true;
            }
        }
          if (tomenu.contains(mouseWorld)) {
            if (Mouse::isButtonPressed(Mouse::Button::Left)) {
                index = 1;
                music.stop();
                cs = true;
            }
        }
    }

    void Render(RenderWindow& window) override {
        window.draw(sprite);
        window.draw(collisionbox);
        tomenu.Draw(window);
        if (finished) {
            if(text.getString() != "You've Beaten The Game!"){nextLevel.Draw(window);}
                
            window.draw(text);
        }
    }

    bool isCollidingWith(const GameObject& other) override {
        if (collisionbox.getGlobalBounds().findIntersection(other.collisionbox.getGlobalBounds()).has_value()) {
            if (other.id == "Player") {
            
                finished = true;
             
             
            }
           
        }
        return false;
    }

    void VectorUse(const vector<GameObject*>& gameObjects) override {
        // Optional: check multiple objects
       
    }

    void HandleWallCollisions(vector<Wall>& levelwalls) override {
        // No-op
    }

   
};
