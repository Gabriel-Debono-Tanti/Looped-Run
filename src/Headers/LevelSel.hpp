#pragma once
#include <SFML/Graphics.hpp>
#include "Objects/Scene.hpp" 
#include "Objects/Button.hpp"
using namespace std;
using namespace sf;
class LevelSel : public Scene
{
private:
    Button l1 = Button("Textures/UI/levels.png", 64, 64);
    Button l2 = Button("Textures/UI/levels.png", 64, 64);
     Button l3 = Button("Textures/UI/levels.png", 64, 64);
     Button l4 = Button("Textures/UI/levels.png", 64, 64 );
     Button l5 = Button("Textures/UI/levels.png", 64, 64 );
      Button l6 = Button("Textures/UI/levels.png", 64, 64 );
      Button l7 = Button("Textures/UI/levels.png", 64, 64 );
      Button l8 = Button("Textures/UI/levels.png", 64, 64 );
     Button backbutton = Button("Textures/UI/Back.png",30,30);
     sf::Music music = Music("Sounds/Menus.wav");
public:
    
    void Init(sf::RenderWindow& window) override;
    void Update(sf::RenderWindow& window) override;
    void Events(sf::RenderWindow& window, const optional<Event>& event) override;
    void Render(sf::RenderWindow& window) override;
    
};

void LevelSel::Init(sf::RenderWindow& window)
{ 
  l2.rect.setTextureRect(IntRect({64, 0 }, {64, 64}));
    l3.rect.setTextureRect(IntRect({128, 0} , {64, 64}));
      l4.rect.setTextureRect(IntRect({192, 0}, {64, 64}));
      l5.rect.setTextureRect(IntRect({256, 0} , {64, 64}));
      l6.rect.setTextureRect(IntRect({320, 0} , {64, 64}));
      l7.rect.setTextureRect(IntRect({384, 0} , {64, 64}));
      l8.rect.setTextureRect(IntRect({448, 0} , {64, 64}));
      l1.SetPosition({150, 100});
      l2.SetPosition( {250, 100});
      l3.SetPosition( {350, 100});
      l4.SetPosition( {450, 100});
      l5.SetPosition( {550, 100});
      l6.SetPosition({650, 100});
      l7.SetPosition({750, 100});
      l8.SetPosition({850, 100});
      backbutton.SetPosition({40, 900});
      backbutton.Scale({3,3});
       music.setLoopPoints({sf::milliseconds(0), sf::seconds(58)});
        music.play();
}

void LevelSel::Update(sf::RenderWindow& window)
{ 
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);
        if(l1.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                index = 2;
                music.stop();
                cs = true;
            }
            }
    if(l2.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                index = 3;
                music.stop();
                cs = true;
            }
            }
     if(l3.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                index = 4;
                music.stop();
                cs = true;
            }
            }
     if(l4.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                index = 5;
                music.stop();
                cs = true;
            }
            }
     if(l5.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                index = 6;
                music.stop();
                cs = true;
            }
            }
     if(l6.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                index = 7;
                music.stop();
                cs = true;
            }
            }
      if(l7.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                index = 8;
                music.stop();
                cs = true;
            }
            }
        if(l8.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                index = 9;
                music.stop();
                cs = true;
            }
            }
    if(backbutton.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                index = 0;
                music.stop();
                cs = true;
            }
            }
}

void LevelSel::Events(sf::RenderWindow& window, const optional<Event>& event)
{ 
    
}

void LevelSel::Render(sf::RenderWindow& window)
{ 
    window.clear(Color::White);
    backbutton.Draw(window);
    
     l1.Draw(window);
     l2.Draw(window);
     l3.Draw(window);
     l4.Draw(window);
     l5.Draw(window);
     l6.Draw(window);
     l7.Draw(window);
     l8.Draw(window);
}
