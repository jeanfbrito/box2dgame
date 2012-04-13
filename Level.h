#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Constants.h"
#include "tinyxml/tinyxml.h"
#include "DebugDraw.h"
#include "DynamicBall.h"
#include "DynamicBox.h"
#include "ContactListener.h"
#include "StaticBox.h"
#include "ResourceManager.h"
#include <Thor/Time/StopWatch.hpp>
#include "Chest.h"

const int LEVEL_WIDTH = 2000;

class Level
{
    public:
        Level(const std::string& levelFilename, sf::RenderWindow* window);
        ~Level();

        void draw();
        void update();
        void handle();

        bool isCompleted(){return completed;}


    private:
        void adjustView();
        void resetView();
        void clear();
        void loadFile(const std::string& filename);
        int width;
        int height;
        bool previewMode;
        bool completed;
        bool allChestsOpened;

        sf::Text nextLevelText;
        std::vector<DynamicBall*> balls;
        std::vector<DynamicBox*> boxes;
        std::vector<Chest*> chests;
        std::vector<StaticBox*> statics;
        b2World* world;
        sf::Sprite background;
        DebugDraw* debugdrawer;
        ContactListener listener;
        sf::RenderWindow* window;
        sf::View view;
        sf::Clock showLevelClock;
        thor::StopWatch stopwatch;
        bool debug;

};

#endif // LEVEL_H
