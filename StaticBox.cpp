#include "StaticBox.h"

StaticBox::StaticBox(float x, float y, float width, float height, b2World& world) : Collidable("StaticBox")
{
    b2BodyDef DEF;
    b2PolygonShape SHAPE;
    b2FixtureDef FIX;

    DEF.position.Set((x+width/2.f)/PPM, (y+height/2.f)/PPM);


    RECT = sf::RectangleShape(sf::Vector2f(width, height));
    RECT.setOrigin(width/2.f, height/2.f);
    RECT.setFillColor(sf::Color(50, 100, 100));
    RECT.setPosition(x+width/2.f, y+height/2.f);
    RECT.setOutlineColor(sf::Color::Black);
    RECT.setOutlineThickness(1);

    SHAPE.SetAsBox(width/2.f/PPM, height/2.f/PPM);

    body = world.CreateBody(&DEF);

    FIX.shape = &SHAPE;
    FIX.density = 0.f;
    FIX.friction = .7f;
    FIX.restitution = 0.0;

    body->CreateFixture(&FIX);
    body->SetUserData(this);
}

StaticBox::~StaticBox()
{
    body->DestroyFixture(body->GetFixtureList());
    body->GetWorld()->DestroyBody(body);
}

void StaticBox::draw(sf::RenderWindow* window)
{
    window->draw(RECT);
}
