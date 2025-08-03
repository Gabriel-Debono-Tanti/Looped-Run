#pragma once
#include "GameObject.hpp"
class GameObjTemp : public GameObject
{
private:
    
public:
    GameObjTemp(/* args */);
    void Init(RenderWindow& window) override{

    }
    void Update(RenderWindow& window) override{
        
    }
    void Render(RenderWindow& window) override{
        
    }
    void VectorUse(const vector<GameObject*>& gameObjectsr) override{
        
    }
    bool isCollidingWith(const GameObject& other)override{
        
    }
    void HandleWallCollisions(vector<Wall>& levelwalls)override{
        
   }
    ~GameObjTemp();
};

GameObjTemp::GameObjTemp(/* args */)
{
     id = "";
}

GameObjTemp::~GameObjTemp()
{
}
