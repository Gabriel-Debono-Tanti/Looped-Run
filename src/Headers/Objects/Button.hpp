#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;
class Button
{
private:
   
    Texture texture;
    
    int width, height;
public:
Sprite rect = Sprite(texture);
    Button(const string& filename,  int w, int h);
    ~Button();
    
    
    void Draw(RenderWindow& window){
        window.draw(rect);
    }
    void SetPosition(Vector2f position){
        rect.setPosition(position);
    }
    void Onhover(int row){
        rect.setTextureRect(IntRect({0,row},{width, height}));
    }
    void OnhoverExit(int row){
        rect.setTextureRect(IntRect({0,row},{width, height}));
    }
     bool contains(const sf::Vector2f& point) const {
        sf::FloatRect bounds = rect.getGlobalBounds();
        return bounds.contains(sf::Vector2f(point));
    }
    void Scale(Vector2f scale){
        rect.setScale(scale);
    }
};

Button::Button(const string& filename, int w, int h)
{
    width = w;
    height = h;
    texture.loadFromFile(filename);
    rect.setTextureRect(IntRect({0,0},{width, height}));
    rect.setTexture(texture);
}

Button::~Button()
{
}
