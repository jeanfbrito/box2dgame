#ifndef STATICBOX_H
#define STATICBOX_H
#include "Collidable.h"
#include <SFML/Graphics.hpp>
#include "Constants.h"

class StaticBox : public Collidable
{
    public:
        StaticBox(float x, float y, float width, float height, b2World& world);
        ~StaticBox();

        void draw(sf::RenderWindow* window);

    private:
        sf::RectangleShape RECT;
};

#endif // STATICBOX_H
