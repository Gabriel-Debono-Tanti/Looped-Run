#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Headers/Objects/Scene.hpp"
#include "Headers/Level1.hpp"
#include "Headers/Level2.hpp"
#include "Headers/Level3.hpp"
#include "Headers/GameScene.hpp"
#include "Headers/LevelSel.hpp"
#include "Headers/MainScene.hpp"
#include "Headers/Level4.hpp"
#include "Headers/Level5.hpp"
#include "Headers/Level6.hpp"
#include "Headers/Level7.hpp"
#include "Headers/Level8.hpp"
#include "vector"
#include <optional>
using namespace std;
using namespace sf;
int main()
{
    auto window = RenderWindow(VideoMode({1920u, 1080u}), "CMake SFML Project");
   window.setFramerateLimit(144);
    vector<Scene*> scenes = { new MainScene, new LevelSel, new Level1, new Level2, new Level3, new Level4, new Level5, new Level6, new Level7, new Level8};
    Scene* currentscene = scenes[currentscene->index];
    currentscene->Init(window);
    
    while (window.isOpen())
    {
        if (currentscene->cs) {
            
        scenes.clear();
        scenes = { new MainScene, new LevelSel, new Level1, new Level2, new Level3, new Level4, new Level5, new Level6, new Level7, new Level8};
        currentscene = scenes[currentscene->index];
        currentscene->Init(window);
        currentscene->cs = false;
        }
       
        while (const std::optional<Event> event = window.pollEvent())
        {
            
            currentscene->Events(window, event);
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                
            }
            if(Keyboard::isKeyPressed(Keyboard::Key::Num1)){
                currentscene->cs = true;
                currentscene->index = 1;
            }
            if(Keyboard::isKeyPressed(Keyboard::Key::Num0)){
                currentscene->cs = true;
                currentscene->index = 0;
            }
            
        }
        
        currentscene->checkCollisions();
        
        currentscene->Update(window);
        window.clear();
        currentscene->Render(window);
        window.display();
        
    }
    return 0;
}
