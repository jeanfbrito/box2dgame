#include "Level.h"
#include <fstream>

Level::Level(const std::string& levelFilename, sf::RenderWindow* window) : debug(false), window(window), completed(false)
{
    world = new b2World(b2Vec2(0, 9.8f));
    debugdrawer = new DebugDraw(window);
    world->SetDebugDraw(debugdrawer);
    world->SetContactListener(&listener);
    showLevelClock.restart();
    view = window->getDefaultView();
    view.move(500, 0);
    window->setView(view);

    background.setTexture(rm->getTexture("background.png"));
    background.setPosition(0, HEIGHT - background.getGlobalBounds().height);
    loadFile(levelFilename);
    previewMode = true;

    nextLevelText.setCharacterSize(25);
    nextLevelText.setString("Press Enter for next level!");
}

void Level::loadFile(const std::string& filename)
{
    statics.push_back(new StaticBox(20*31, HEIGHT-3*31, WIDTH + 500, 3, *world));
    statics.push_back(new StaticBox(LEVEL_WIDTH, 0, 3, HEIGHT, *world));
    statics.push_back(new StaticBox(0, HEIGHT, LEVEL_WIDTH, 3, *world));


    balls.push_back(new DynamicBall(225, 600, 15, *world));


    std::ifstream file(filename.c_str());
    int size;
    file >> size;
    float x, y, rot;
    std::string name;
    for(int i = 0; i < size; i++)
    {
        file >> x >> y >> rot >> name;
        std::string temp;
        getline(file, temp);
        if(name != "chest.txt")
            boxes.push_back(new DynamicBox(name, x+600, y + (168-96), rot, *world));
        else
            chests.push_back(new Chest(x+600, y + (168-96), rot, *world));
    }
}

void Level::draw()
{

    window->draw(background);
    for(int i = 0; i < boxes.size(); i++)
        boxes[i]->draw(window);
    for(int i = 0; i < chests.size(); i++)
        chests[i]->draw(window);


    if(!previewMode)
    {
        adjustView();
        for(int i = 0; i < balls.size(); i++)
            balls[i]->draw(window);
    }

    if(allChestsOpened)
    {
        nextLevelText.setPosition(window->convertCoords(sf::Vector2i(WIDTH/2.f - 75, HEIGHT/2.f - 25), window->getView()));
        window->draw(nextLevelText);
    }

    if(debug)
        world->DrawDebugData();
}

void Level::update()
{
    world->Step(timeStep, 12, 5);
    for(int i = 0; i < balls.size(); i++)
        balls[i]->update(sf::Vector2i(window->convertCoords(sf::Mouse::getPosition(*window), window->getView())));
    for(int i = 0; i < boxes.size(); i++)
        boxes[i]->update();
    allChestsOpened = true;
    for(int i = 0; i < chests.size(); i++)
    {
        chests[i]->update();
        if(!chests[i]->isOpen())
            allChestsOpened = false;
    }

    if(previewMode)
    {
        if(showLevelClock.getElapsedTime() > sf::seconds(2))
        {
            sf::View view = window->getView();
            view.move(-3, 0);
            window->setView(view);
        }
        if(window->getView().getCenter().x < WIDTH/2)
        {
            window->setView(window->getDefaultView());
            previewMode = false;
        }
    }

    if(balls.back()->isHit() && !allChestsOpened) //check if we need to start a new ball
    {
        for(int i = 0; i < boxes.size(); i++)
        {
            if(boxes[i]->isAwake())
                return;
        }
        for(int i = 0; i < chests.size(); i++)
        {
            if(chests[i]->isAwake())
                return;
        }
        for(int i = 0; i < balls.size(); i++)
        {
            if(balls[i]->isAwake())
                return;
        }
        if(stopwatch.getElapsedTime() > sf::seconds(1.5)) //to show the aftermath of the hit
        {
            balls.push_back(new DynamicBall(225, 600, 15, *world));
            resetView();
            stopwatch.reset(false);
        }
        else if(stopwatch.isRunning() == false)
            stopwatch.start();
    }
}

void Level::handle()
{
    sf::Event Event;
    while (window->pollEvent(Event))
    {
        switch (Event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                {
                    if(Event.key.code == sf::Keyboard::Return && previewMode)
                    {
                        previewMode = false;
                        resetView();
                    }
                    else if(Event.key.code == sf::Keyboard::D)
                    {
                        debug = !debug;
                        return;
                    }
                    else if(Event.key.code == sf::Keyboard::Return && allChestsOpened)
                    {
                        completed = true;
                    }
                    else if(Event.key.code == sf::Keyboard::Space)
                    {
                        clear();
                        loadFile("level.txt");
                        resetView();
                    }
                }

            case sf::Event::MouseButtonPressed:
                {
                    if(Event.mouseButton.button == sf::Mouse::Left && !previewMode)
                        balls.back()->shoot(window->convertCoords(sf::Mouse::getPosition(*window), window->getView()).x, window->convertCoords(sf::Mouse::getPosition(*window), window->getView()).y);
                    break;
                }
            default:
                break;
        }
    }
}

void Level::adjustView()
{
    if(balls.back()->isHit()) //if we hit the target, pause the screen right there.
        return;

    bool outOfScreenY = false;
    bool outOfScreenX = false;
    sf::Vector2f pos = balls.back()->getPosition();

    if(pos.x - WIDTH/2 < 0)
        outOfScreenX = true;

    if(pos.x + WIDTH/2 > background.getGlobalBounds().width)
        outOfScreenX = true;


    if(!outOfScreenX)
    {
        view = window->getView();
        view.setCenter(static_cast<int>(pos.x), static_cast<int>(view.getCenter().y));
        window->setView(view);
    }
}

void Level::resetView()
{
    window->setView(window->getDefaultView());
}

void Level::clear()
{
    for(auto itr = boxes.begin(); itr != boxes.end();)
    {
        delete (*itr);
        itr = boxes.erase(itr);
    }
    for(auto itr = balls.begin(); itr != balls.end();)
    {
        delete (*itr);
        itr = balls.erase(itr);
    }
    for(auto itr = statics.begin(); itr != statics.end();)
    {
        delete (*itr);
        itr = statics.erase(itr);
    }
    for(auto itr = chests.begin(); itr != chests.end();)
    {
        delete (*itr);
        itr = chests.erase(itr);
    }
}

Level::~Level()
{
    clear();
}
