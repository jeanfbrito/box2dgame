#ifndef DYNAMICBALL_H
#define DYNAMICBALL_H
#include "ResourceManager.h"
#include "Collidable.h"
#include <SFML/Graphics.hpp>
#include "Constants.h"


class DynamicBall : public Collidable
{
    public:
        DynamicBall(float x, float y, float radius, b2World& world);
        ~DynamicBall();

        void draw(sf::RenderWindow* window);
        void update(sf::Vector2i mousePos);
        bool isHit(){return hit;}
        bool isFlying(){return flying;}

        void onCollisionBegin(const std::string& name, b2Contact* contact);
        void onCollisionEnd(const std::string& name, b2Contact* contact);

        void shoot(float x, float y);
        sf::Vector2f getPosition(){return sprite.getPosition();}//sf::Vector2f(body->GetPosition().x, body->GetPosition().y);}


    private:
        bool flying;
        bool hit;
        sf::Sprite sprite;
        sf::VertexArray line;
};

#endif // DYNAMICBALL_H
