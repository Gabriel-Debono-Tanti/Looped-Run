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
class GameScene : public Scene
{
private:
    Player player;
    EnemyAI1 enemytype1;
    EnemyAI2 enemytype2;
    Wall wall;
    vector<Wall> walls;
    TilemapImporter tmp;
    vector<Sprite> tiles;
    DamageArea d;
    bool lKeyHeld;
    PushBlock p;
    PushButton pb = PushButton( 1);
    Door door = Door(1, {300, 710});
    Goal goal;
    Music music = Music("Sounds/GameMusic.wav");
public:
    
    void Init(sf::RenderWindow& window) override;
    void Update(sf::RenderWindow& window) override;
    void Events(sf::RenderWindow& window, const optional<Event>& event)override;
    void Render(sf::RenderWindow& window) override;
    
};

void GameScene::Init(sf::RenderWindow& window)
{ 
    music.setLoopPoints({sf::milliseconds(0), sf::seconds(38)});
     music.play();
  tmp.Init("Levels/testlevel.json", "Textures/tilemap.png", Vector2i(60, 34), Vector2i(32, 32), Vector2i(2048, 2048));
  tiles = tmp.Layer();
  walls = tmp.TilemapWalls();
  goal.Init(window);
  goal.setPosition({200, 700});
  door.Init(window);
 player.Init(window);
 p.Init(window);
 pb.Init(window);
 pb.setPosition({200, 700});enemytype2.Init(window);
 player.setPosition({0, 100});
 d.collisionbox.setSize({200, 100});
 d.collisionbox.setPosition({0, 400});
 
 enemytype1.Init(window);
 
 gameObjects.push_back(&pb);
 gameObjects.push_back(&p);gameObjects.push_back(&goal);
 gameObjects.push_back(&player);
 gameObjects.push_back(&door);
 
 //gameObjects.push_back(&enemytype1);
 gameObjects.push_back(&enemytype2);
 gameObjects.push_back(&d);
 wall.Wallbox.setSize({1000,30});
 wall.setPos({10, 800});
 wall.issemistatic = true;
 wall.Wallbox.setFillColor(Color::Green);
 walls.push_back(wall);


}

void GameScene::Update(sf::RenderWindow& window)
{ 
  
 

//std::stable_sort(gameObjects.begin(), gameObjects.end(), compare);

 for(auto& g : gameObjects){
 g->VectorUse(gameObjects);
 g->HandleWallCollisions(walls);
g->Update(window);
if(auto go = dynamic_cast<Goal*>(g)){
    go->Next(music, index, cs, window);
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

inline void GameScene::Events(sf::RenderWindow& window, const optional<Event>& event)
{ 
    if (const auto type = event->getIf<Event::KeyPressed>()) {
        if(type->scancode == sf::Keyboard::Scancode::L && !lKeyHeld){
    lKeyHeld = true; // Mark as held so it won't repeat

    // Do your Recording logic
    auto r = new Recording();
    r->Init(window);

    for (auto& g : gameObjects) {
        if (Player* aPtr = dynamic_cast<Player*>(g)) {
            aPtr->setPosition({0, 300});
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

void GameScene::Render(sf::RenderWindow& window)
{ 
    window.clear(Color::Blue);
    for(auto& tile : tiles)
        window.draw(tile);
    for(auto& g : gameObjects)
    g->Render(window);
    for(auto& w : walls)
    w.drawTo(window);
}
