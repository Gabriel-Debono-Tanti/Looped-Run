#pragma once
#include "GameObject.hpp"

class PushButton : public GameObject {
private:
    bool pressedThisFrame = false;

public:
    bool ispressed = false;
    int Design, bc;

    PushButton(int code) {
        id = "PushButton";
        scale = 2;
        bc = code;
        isstatic = false;
    }

    void Init(sf::RenderWindow& window) override {
        SetTexture("Textures/button.png", IntRect({0, 0}, {30,8}));
     

        collisionbox.setFillColor(Color(255, 0, 0, 128));

        Animation idle = Animation(0, 1, 100);
        idle.getframe({30,8});
        Animation pressed = Animation(1, 1, 100);
        pressed.getframe({30,8});
        ani.emplace("Idle", idle);
        ani.emplace("Pressed", pressed);
        Setanimation("Idle");
    }

    void Update(sf::RenderWindow& window) override {
        RunAnimation();

        collisionbox.setSize({ sprite.getGlobalBounds().size.x, sprite.getGlobalBounds().size.y });
        collisionbox.setPosition(sprite.getPosition());

        // Finalize press state for this frame
        ispressed = pressedThisFrame;
        pressedThisFrame = false;

        Setanimation(ispressed ? "Pressed" : "Idle");
    }

    void Render(sf::RenderWindow& window) override {
        window.draw(sprite);
        // window.draw(collisionbox); // optional for debugging
    }

    // Check collision and mark for press
    bool isCollidingWith(const GameObject& other) override {
        if (collisionbox.getGlobalBounds().findIntersection(other.collisionbox.getGlobalBounds()).has_value()) {
            if (other.id == "Player" || other.id == "Recording" || other.id == "PushBlock" || other.id == "Enemy") {
                pressedThisFrame = true;
            }
        }
        return false;
    }

    void VectorUse(const vector<GameObject*>& gameObjects) override {
        // Nothing here anymore — press state is handled entirely via isCollidingWith
    }
};
