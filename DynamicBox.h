#ifndef DYNAMICBOX_H
#define DYNAMICBOX_H
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Collidable.h"

class DynamicBox : public Collidable
{
    public:
        DynamicBox(std::string name, float x, float y, float rotation, b2World& world);
        virtual ~DynamicBox();

        void draw(sf::RenderWindow* window);
        virtual void update();
        void jump(float power);
        void setColor(const sf::Color& color);
        void setRotatable(bool rot);
        std::string getName(){return name;}
        sf::FloatRect getBounds(){return sprite.getGlobalBounds();}
        float getRotation(){return body->GetAngle();}
        void postSolve(b2Contact *contact, const b2ContactImpulse *impulse);


    protected:
        b2BodyDef DEF;
        b2PolygonShape SHAPE;
        b2FixtureDef FIX;
        sf::Sprite sprite;
        bool rotatable;
};

#endif // DYNAMICBOX_H
