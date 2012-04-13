#include <iostream>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Constants.h"
#include "Level.h"


using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT,32),"Application");
    window.setFramerateLimit(60);




    Level* level;
    std::vector<std::string> levelfiles;
    levelfiles.push_back("level1.txt");
    levelfiles.push_back("level2.txt");
    levelfiles.push_back("level3.txt");
    int currentLevel = 0;

    level = new Level("level1.txt", &window);

    while(window.isOpen())
    {
        level->update();
        level->handle();
        window.clear(sf::Color(200, 200, 200));
        level->draw();
        window.display();
        if(level->isCompleted())
        {
            delete level;
            level = new Level(levelfiles[++currentLevel], &window);
        }
    }

    return 0;
}
