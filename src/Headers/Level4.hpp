#pragma once
#include <SFML/Graphics.hpp>
#include "Objects/Scene.hpp"
#include "Objects/Player.hpp"
#include "Objects/Enemy.hpp"
#include "Objects/EnemyAI1.hpp"
#include "Objects/EnemyAI2.hpp"
#include "Objects/TilemapImporter.hpp"
#include "Objects/DamageArea.hpp"
#include "Objects/Recording.hpp"
#include "Objects/PushBlock.hpp"
#include "Objects/PushButton.hpp"
#include "Objects/Door.hpp"
#include "Objects/Goal.hpp"
#include <algorithm>
using namespace std;
using namespace sf;
class Level4 : public Scene
{
private:
   Font font = Font("Fonts/font2.otf");
    Text text = Text(font);
    sf::Music music = Music("Sounds/GameMusic.wav");
    vector<Wall> walls, semistaticwalls;
    TilemapImporter tmp;
    vector<Sprite> tiles;
    Goal goal;
vector<PushButton> buttons;
vector<PushBlock> blocks;
vector<Player> players;
vector<EnemyAI2> ais;
vector<Door> doors;
    bool lKeyHeld = true;
    
public:
    
    void Init(sf::RenderWindow& window) override;
    void Update(sf::RenderWindow& window) override;
    void Events(sf::RenderWindow& window, const optional<Event>& event)override;
    void Render(sf::RenderWindow& window) override;
    
};

void Level4::Init(sf::RenderWindow& window)
{ 
      music.setLoopPoints({sf::milliseconds(0), sf::seconds(38)});
        music.play();
  tmp.Init("Levels/Level4.json", "Textures/tilemap.png", Vector2i(60, 34), Vector2i(32, 32), Vector2i(2048, 2048));
  tiles = tmp.Layer();
  walls = tmp.TilemapWalls();
  for(auto& e : tmp.SemiWalls()){
    walls.push_back(e);
  }  
  goal.Init(window);
   goal.setPosition({1700,430});
    gameObjects.push_back(&goal);

    buttons = tmp.Buttons();
    for (auto& g : buttons) {
        g.Init(window);
        gameObjects.push_back(&g);
    }

    blocks = tmp.Blocks();
    for (auto& g : blocks) {
        g.Init(window);
        gameObjects.push_back(&g);
    }

    players = tmp.Players();
    for (auto& g : players) {
        g.Init(window);
        gameObjects.push_back(&g);
    }

    ais = tmp.AIs();
    for (auto& g : ais) {
        g.Init(window);
        gameObjects.push_back(&g);
    }

    doors = tmp.Doors();
    for (auto& g : doors) {
        g.Init(window);
        gameObjects.push_back(&g);
    }
    
        text.setCharacterSize(40);
        text.setPosition({770, 540});
        text.setFillColor(sf::Color::Black);
 


 
 


}

void Level4::Update(sf::RenderWindow& window)
{ 
   if(goal.finished){
    music.stop();
  }
 

//std::stable_sort(gameObjects.begin(), gameObjects.end(), compare);

 for(auto& g : gameObjects){
 g->VectorUse(gameObjects);
 g->HandleWallCollisions(walls);
g->Update(window);
if(auto go = dynamic_cast<Goal*>(g)){
    go->Next(music,index, cs, window);
}
if (auto door = dynamic_cast<Door*>(g)) {
        for(auto& g2 : gameObjects){
        
            if (auto button = dynamic_cast<PushButton*>(g2)) {
                if (door->dc == button->bc) {
                    door->open = button->ispressed;
                    // You can now trigger something or link them
                }
            }
        
        } 
    }
}

//if (sf::Keyboard::isKeyPressed(Keyboard::Key::L)) {
  //  Recording* r = new Recording();
   // r->Init(window);

   // for (auto& g : gameObjects) {
  //      if (Player* aPtr = dynamic_cast<Player*>(g)) {
  //          aPtr->setPosition({0, 300});
  //          r->prec = aPtr->recording;
  //          aPtr->recording.clear();
     //   }
 //   }

//    gameObjects.push_back(r); // Safe: r is heap-allocated
    
//}
}

inline void Level4::Events(sf::RenderWindow& window, const optional<Event>& event)
{ 
    if (const auto type = event->getIf<Event::KeyPressed>()) {
        if(type->scancode == sf::Keyboard::Scancode::L && !lKeyHeld){
    lKeyHeld = true; // Mark as held so it won't repeat

    // Do your Recording logic
    auto r = new Recording();
    r->Init(window);

    for (auto& g : gameObjects) {
        if (Player* aPtr = dynamic_cast<Player*>(g)) {
            aPtr->setPosition({220, 480});
            r->prec = aPtr->recording;
            aPtr->recording.clear();
            gameObjects.push_back(r);
        }
         if (Recording* aPtr = dynamic_cast<Recording*>(g)) {
            aPtr->currentIndex = 0;
            aPtr->playbackFinished = false;
         }
    }

    
}
}

// Reset the hold flag when L is released
 if (const auto type = event->getIf<Event::KeyReleased>()) {
if (type->scancode == sf::Keyboard::Scancode::L) 
        lKeyHeld = false;
}
}

void Level4::Render(sf::RenderWindow& window)
{ 
    window.clear(Color::Blue);
    for(auto& tile : tiles)
        window.draw(tile);
    for(auto& g : gameObjects)
    g->Render(window);
    for(auto& w : walls)
    w.drawTo(window);
    window.draw(text);
}
