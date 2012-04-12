#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Constants.h"
#include "tinyxml/tinyxml.h"
#include "PlayerBox.h"
#include "Tile.h"
#include <iostream>
#include "DebugDraw.h"
#include "DynamicBall.h"
#include "DynamicBox.h"
#include "ContactListener.h"

const int LEVEL_WIDTH = 2000;

class Level
{
    public:
        Level(const std::string& levelFilename, sf::RenderWindow* window);
        ~Level();

        void draw();
        void update();
        void handle();


    private:
        void adjustView();
        void resetView();
        void clear();
        void loadFile(const std::string& filename);
        int width;
        int height;
        bool previewMode;

        std::vector<DynamicBall*> balls;
        std::vector<DynamicBox*> boxes;
        std::vector<StaticBox*> statics;
        b2World* world;
        sf::Sprite background;
        DebugDraw* debugdrawer;
        ContactListener listener;
        sf::RenderWindow* window;
        sf::View view;
        sf::Clock showLevelClock;
        bool debug;

};

#endif // LEVEL_H
