#pragma once
#include <map>

using namespace std;
struct Animation
{
    int vertspace;
    int index;
    int frames;
    int speed;
    Vector2i frame;
    Animation(){}
    Animation(int i, int f, int s){
        index = i;
        frames = f;
        speed = s;
    }
    void getframe(Vector2i fr){
        frame = fr;
    }
    
};