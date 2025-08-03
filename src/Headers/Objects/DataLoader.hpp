#pragma once
#include <stdio.h>
#include <array>
#include <string>
#include <iostream>
#include <fstream>
#include <array>
using namespace std;

struct GameData
{
    float posx;
    float posy;
    float health = 100;
    
};
struct KeyboardSettings
{
  Keyboard::Key UpKey = Keyboard::W;
  Keyboard::Key DownKey = Keyboard::S;
  Keyboard::Key LeftKey = Keyboard::A;
  Keyboard::Key RightKey = Keyboard::D;
};
struct DisplaySettings{
  int Colourblindness = 0;
  bool isFullscreen = false;
  ContextSettings settings;
};


class DataLoader
{
private:
   string dir = "./saves/";
public:
    DataLoader();
    void SaveGameData(int savefile,const GameData &game);
    void LoadGameData(int savefile, GameData& game);
    void SaveKeyboardSettings(string savefile,const KeyboardSettings &game);
    void LoadKeyboardSettings(string savefile, KeyboardSettings& game);
    void SaveDisplaySettings(string savefile,const DisplaySettings& game);
    void LoadDisplaySettings(string savefile, DisplaySettings& game);
    ~DataLoader();
};

DataLoader::DataLoader()
{
    
}

void DataLoader::SaveGameData(int savefile,const GameData& game)
{
    string filename = dir + to_string(savefile) + ".ddata";
    ofstream file(filename, ios::binary);
    if (file.is_open())
    {
        
        file.write(reinterpret_cast<const char*>(&game), sizeof(game));
    

        file.close();
    }
   
    
}
void DataLoader::SaveKeyboardSettings(string savefile,const KeyboardSettings& game)
{
    string filename = dir + savefile + ".ddata";
    ofstream file(filename, ios::binary);
    if (file.is_open())
    {
        
        file.write(reinterpret_cast<const char*>(&game), sizeof(game));
    

        file.close();
    }
   
    
}
void DataLoader::LoadGameData(int savefile, GameData& game)
{
    string filename = dir + to_string(savefile) + ".ddata";
    ifstream file(filename, ios::binary);
    if (file.is_open())
    {
       
        file.read(reinterpret_cast<char*>(&game), sizeof(game));
        

        file.close();
        }
    
}
void DataLoader::LoadKeyboardSettings(string savefile, KeyboardSettings& game)
{
    string filename = dir + savefile + ".ddata";
    ifstream file(filename, ios::binary);
    if (file.is_open())
    {
       
        file.read(reinterpret_cast<char*>(&game), sizeof(game));
        

        file.close();
        }
    
}
void DataLoader::LoadDisplaySettings(string savefile, DisplaySettings& game)
{
    string filename = dir + savefile + ".ddata";
    ifstream file(filename, ios::binary);
    if (file.is_open())
    {
       
        file.read(reinterpret_cast<char*>(&game), sizeof(game));
        

        file.close();
        }
    
}
void DataLoader::SaveDisplaySettings(string savefile,const DisplaySettings& game)
{
    string filename = dir + savefile + ".ddata";
    ofstream file(filename, ios::binary);
    if (file.is_open())
    {
        
        file.write(reinterpret_cast<const char*>(&game), sizeof(game));
    

        file.close();
    }
   
    
}
DataLoader::~DataLoader()
{
}
