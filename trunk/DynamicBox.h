#ifndef DYNAMICBOX_H
#define DYNAMICBOX_H
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Collidable.h"
#include "ResourceManager.h"

class DynamicBox : public Collidable
{
    public:
        DynamicBox(std::string name, float x, float y, float rotation, b2World& world);
        virtual ~DynamicBox();

        void draw(sf::RenderWindow* window);
        virtual void update();
        void jump(float power);
        std::string getName(){return name;}
        sf::FloatRect getBounds(){return sprite.getGlobalBounds();}
        float getRotation(){return body->GetAngle();}



    protected:
        b2BodyDef DEF;
        b2PolygonShape SHAPE;
        b2FixtureDef FIX;
        sf::Sprite sprite;
};

#endif // DYNAMICBOX_H
