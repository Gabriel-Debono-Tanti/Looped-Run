#pragma once
#include <SFML/Graphics.hpp>
#include "Objects/Scene.hpp" 
#include "Objects/Button.hpp"
#include "Objects/TilemapImporter.hpp"
using namespace std;
using namespace sf;
class MainScene : public Scene
{
private:
    Button toGame = Button("Textures/UI/Play.png", 64, 32 );
     //Button toSettings = Button("Textures/SettingsButton.png", 68, 28, {-(69*3)/2, 90});
     Button Quit = Button("Textures/UI/Quit.png", 64, 32);
      sf::Music music = Music("Sounds/Menus.wav");
        vector<Sprite> tiles;
      TilemapImporter tmp;
      Texture tex = Texture("Textures/Logo.png"); 
      Sprite Logo = Sprite(tex);
public:
    
    void Init(sf::RenderWindow& window) override;
    void Update(sf::RenderWindow& window) override;
    void Events(sf::RenderWindow& window, const optional<Event>& event) override;
    void Render(sf::RenderWindow& window) override;
    
};

void MainScene::Init(sf::RenderWindow& window)
{ 
    tmp.Init("Levels/main.json", "Textures/tilemap.png", Vector2i(60, 34), Vector2i(32, 32), Vector2i(2048, 2048));
    tiles = tmp.Layer();
 toGame.Scale(Vector2f(3, 3));
 toGame.SetPosition({800, 500});
        Quit.Scale(Vector2f(3, 3));
        Quit.SetPosition({800, 700});
         music.setLoopPoints({sf::milliseconds(0), sf::seconds(58)});
        music.play();
        
        Logo.setPosition({650, 100});
        Logo.setScale({5,5});
}

void MainScene::Update(sf::RenderWindow& window)
{ 
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);
        if(toGame.contains(mousePosF)){
           if(Mouse::isButtonPressed(Mouse::Button::Left)){
                index = 1;
                music.stop();
                cs = true;
           }
        }
        if(Quit.contains(mousePosF)){
             if(Mouse::isButtonPressed(Mouse::Button::Left)){
                 window.close();
             }
          
        }
}

void MainScene::Events(sf::RenderWindow& window, const optional<Event>& event)
{ 
    
}

void MainScene::Render(sf::RenderWindow& window)
{ 
    window.clear(Color::White);
    for(auto& tile : tiles)
        window.draw(tile);
    toGame.Draw(window);
    Quit.Draw(window);
    window.draw(Logo);
}
