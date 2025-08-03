#pragma once
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include "Wall.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <ctime>
#include "Player.hpp"
#include "PushBlock.hpp"
#include "PushButton.hpp"
#include "Door.hpp"
#include "Goal.hpp"
using json = nlohmann::json;
using namespace sf;
using namespace std;
class TilemapImporter
{
private:
    int y = 0;
    int x = 0;
    json level;
    Vector2i Tilesize, Tilemapsize;
    vector<Sprite> maptextures;
    Texture Tilesettexture;
public:

    ~TilemapImporter();
    void Init(const string& filename, const string& textureFile, Vector2i tilemapsize, Vector2i tilesize, Vector2i texturedim);
  
    
    vector<Wall> TilemapWalls(){
        vector<Wall> walls;
        for(const auto& element : level["layers"][7]["objects"]){

            Wall wall; wall.Wallbox.setSize(Vector2f(element["width"], element["height"]));
            wall.setPos(Vector2f(element["x"], element["y"]));
            wall.Wallbox.setFillColor(Color::Transparent);
            walls.push_back(wall);
           //cout << element << endl;
        }
        return walls;
    };
    vector<Wall> SemiWalls(){
        vector<Wall> walls;
        for(const auto& element : level["layers"][8]["objects"]){

            Wall wall; wall.Wallbox.setSize(Vector2f(element["width"], element["height"]));
            wall.setPos(Vector2f(element["x"], element["y"]));
            wall.Wallbox.setFillColor(Color::Transparent);
            wall.issemistatic = true;
            walls.push_back(wall);
           //cout << element << endl;
        }
        return walls;
    };
    vector<Sprite> Layer(){
       vector<Sprite> tilemap;
        float posx = 0;
        float posy = 0;
        for(const auto& element : level["layers"][0]["data"]){
            int value = element.get<int>();
        
            if(posx == Tilemapsize.x){
                    posx = 0;
                    posy += Tilesize.y;
                
            }
            if(value == 0){
                posx += Tilesize.x;
               
            }
            if(value != 0){
                Sprite tile= maptextures[value - 1];
            
                tile.setPosition({posx, posy});
            
                tilemap.push_back(tile);
                posx += Tilesize.x;  
               
            }
        }
        return tilemap;
    }
    vector<Player> Players(){
       vector<Player> tilemap;
        float posx = 0;
        float posy = 0;
        for(const auto& element : level["layers"][4]["data"]){
            int value = element.get<int>();
        
            if(posx == Tilemapsize.x){
                    posx = 0;
                    posy += Tilesize.y;
                
            }
            if(value == 0){
                posx += Tilesize.x;
               
            }
            if(value != 0){
                Player player;
            
                player.setPosition({posx, posy});
            
                tilemap.push_back(player);
                posx += Tilesize.x;  
               
            }
        }
        return tilemap;
    }
   vector<EnemyAI2> AIs(){
       vector<EnemyAI2> tilemap;
        float posx = 0;
        float posy = 0;
        for(const auto& element : level["layers"][5]["data"]){
            int value = element.get<int>();
        
            if(posx == Tilemapsize.x){
                    posx = 0;
                    posy += Tilesize.y;
                
            }
            if(value == 0){
                posx += Tilesize.x;
               
            }
            if(value != 0){
                EnemyAI2 enemy;
            
                enemy.setPosition({posx, posy});
            
                tilemap.push_back(enemy);
                posx += Tilesize.x;  
               
            }
        }
        return tilemap;
    }
    vector<PushButton> Buttons(){
       vector<PushButton> tilemap;
        float posx = 0;
        float posy = 0;
        for(const auto& element : level["layers"][2]["data"]){
            int value = element.get<int>();
        
            if(posx == Tilemapsize.x){
                    posx = 0;
                    posy += Tilesize.y;
                
            }
            if(value == 0){
                posx += Tilesize.x;
               
            }
            if(value != 0){
                PushButton pb = PushButton(value-128);
            
                pb.setPosition({posx-32, posy+18});
            
                tilemap.push_back(pb);
                posx += Tilesize.x;
               
            }
        }
        return tilemap;
    }
   vector<Door> Doors(){
       vector<Door> tilemap;
        float posx = 0;
        float posy = 0;
        for(const auto& element : level["layers"][6]["data"]){
            int value = element.get<int>();
        
            if(posx == Tilemapsize.x){
                    posx = 0;
                    posy += Tilesize.y;
                
            }
            if(value == 0){
                posx += Tilesize.x;
               
            }
            if(value != 0){
                Door door = Door(value-192, {posx, posy});
            
                
            
                tilemap.push_back(door);
                posx += Tilesize.x;  
               
            }
        }
        return tilemap;
    }

   
 vector<PushBlock> Blocks(){
       vector<PushBlock> tilemap;
        float posx = 0;
        float posy = 0;
        for(const auto& element : level["layers"][3]["data"]){
            int value = element.get<int>();
        
            if(posx == Tilemapsize.x){
                    posx = 0;
                    posy += Tilesize.y;
                
            }
            if(value == 0){
                posx += Tilesize.x;
               
            }
            if(value != 0){
                PushBlock block;
            
                block.setPosition({posx, posy});
            
                tilemap.push_back(block);
                posx += Tilesize.x;  
               
            }
        }
        return tilemap;
    }
};

void TilemapImporter::Init(const string& filename, const string& textureFile, Vector2i tilemapsize, Vector2i tilesize, Vector2i texturedim)
{
    Tilemapsize = {tilemapsize.x*tilesize.x, tilemapsize.y*tilesize.y};
    Tilesize = tilesize;
    
    if(!Tilesettexture.loadFromFile(textureFile))
        printf("Error in tilemap sprites");
    ifstream f(filename);
    level = json::parse(f);
    for(int i = 0; i < texturedim.x/tilesize.x + texturedim.y/tilesize.y; i++){
         Sprite tile = Sprite(Tilesettexture);
         tile.setTextureRect(IntRect({x,y}, tilesize));
        x += tilesize.x;
        if(x==texturedim.x){
            x=0;
            y+=tilesize.y;
        }
        maptextures.push_back(tile);
    }
}

TilemapImporter::~TilemapImporter()
{
}
