#pragma once


#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Wall
{
private:
    
public:
    RectangleShape Wallbox;
    bool issemistatic = false;
    sf::FloatRect getglobalbounds(){
        return Wallbox.getGlobalBounds();
    }
    int GetY(){
        return Wallbox.getPosition().y;
    }
    int GetX(){
        return Wallbox.getPosition().x;
    }
    Wall(){
        
    }
    void drawTo(sf::RenderWindow &window){
        window.draw(Wallbox);
    }void setPos(sf::Vector2f pos){
        Wallbox.setPosition(pos);
    }

};


