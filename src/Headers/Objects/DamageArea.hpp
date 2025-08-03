#pragma once
#include "GameObject.hpp"
class DamageArea : public GameObject
{
private:
    
public:
    DamageArea(/* args */);
    void Init(RenderWindow& window) override{
        //SetTexture("Textures/");
        collisionbox.setFillColor(Color::Red);
        isstatic = false;

    }
    void Update(RenderWindow& window) override{
        
    }
    void Render(RenderWindow& window) override{
        window.draw(collisionbox);
    }
    void VectorUse(const vector<GameObject*>& gameObjectsr) override{
        
    }
    bool isCollidingWith(const GameObject& other)override{
        return false;
    }
    void HandleWallCollisions(vector<Wall>& levelwalls)override{
        
   }
    ~DamageArea();
};

DamageArea::DamageArea(/* args */)
{
     id = "DamageArea";

}

DamageArea::~DamageArea()
{
}
