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

    Level level("level.txt", &window);

    while(window.isOpen())
    {
        level.update();
        level.handle();
        window.clear(sf::Color(200, 200, 200));
        level.draw();
        window.display();
    }

    return 0;
}
