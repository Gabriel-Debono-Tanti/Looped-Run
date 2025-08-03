#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "Wall.hpp"
#include "Animation.hpp"
using namespace sf;
using namespace std;
class GameObject
{
private:
int frames, index, speed, frameWidth, frameHeight, currentFrame;
Clock ticks;
public:
    Texture tex = Texture("Textures/1.png");
    Sprite sprite = Sprite(tex, IntRect({0, 0}, {(int)tex.getSize().x, (int)tex.getSize().y}));
    RectangleShape collisionbox;
    vector<Wall> walls;
    sf::Vector2f position;
    bool isstatic;
     map<string, Animation> ani;
    float scale = 1;
    bool flip = false;
protected:
    string currentAnim;
public:
    string id = "";
   virtual void Init(RenderWindow& window) = 0;
    virtual void Update(RenderWindow& window) = 0;
    virtual void Render(RenderWindow& window) = 0;

    void setPosition(Vector2f pos) {
        sprite.setPosition(pos);
    }

    Vector2f getPosition() {
        return sprite.getPosition();
    }

    Vector2f getColliderPosition() {
        return collisionbox.getPosition();
    }

    

    void SetTexture(string filepath, IntRect rect) {
        tex.loadFromFile(filepath);
        sprite.setTexture(tex);
        sprite.setTextureRect(rect);
    }

    void SetRotation(float angle) {
        sprite.setRotation(degrees(angle));
    }

   void Setanimation( const string& aniname){
           if (currentAnim != aniname) {
        currentAnim = aniname;
        ticks.restart();
        const Animation& a = ani[aniname];
        frames = a.frames;
        index = a.index;
        speed = a.speed; 
        frameWidth =a.frame.x;
    frameHeight = a.frame.y;}
    };

   void RunAnimation() {
    currentFrame = (int)(((ticks.getElapsedTime().asMilliseconds()) / speed) % frames);
   // cout << ticks.getElapsedTime().asSeconds() << endl;
    sprite.setTextureRect(IntRect(
       Vector2i(frameWidth * currentFrame,
        frameHeight * index),
          Vector2i(frameWidth,
        frameHeight)
    ));

        // Handle flipping
        if (flip) {
            sprite.setScale({ -scale, scale });
            sprite.setOrigin({ (float)frameWidth, 0 });
        } else {
            sprite.setScale({ scale, scale });
            sprite.setOrigin({ 0, 0 });
        }
    }

    virtual void VectorUse(const vector<GameObject*>& gameObjectsr) = 0;
    virtual bool isCollidingWith(const GameObject& other) = 0;
    virtual void HandleWallCollisions(vector<Wall>& levelwalls) {}
};


