#include "DynamicBox.h"

#include <fstream>
#include <iostream>

DynamicBox::DynamicBox(std::string name, float x, float y, float rotation, b2World& world) : Collidable(name)
{
    std::ifstream file(name.c_str());
    float density;
    float friction;
    std::string fileName;
    file >> fileName >> density >> friction;


    sprite.setTexture(rm->getTexture(fileName));
    float width = sprite.getGlobalBounds().width;
    float height = sprite.getGlobalBounds().height;

    sprite.setPosition(x, y);
    sprite.setOrigin(width/2.f, height/2.f);

    DEF.position.Set((x+width/2.f)/PPM, (y+height/2.f)/PPM);
    DEF.type = b2_dynamicBody;
    DEF.angle = rotation;
    DEF.linearDamping = 0.5f;

    SHAPE.SetAsBox(width/2.f/PPM, height/2.f/PPM);

    body = world.CreateBody(&DEF);

    FIX.shape = &SHAPE;
    FIX.density = density;
    FIX.friction = friction;
    //FIX.linearDamping = .2;
    FIX.restitution = 0.0;

    body->CreateFixture(&FIX);
    body->SetUserData(this);
}

DynamicBox::~DynamicBox()
{
    body->DestroyFixture(body->GetFixtureList());
    body->GetWorld()->DestroyBody(body);
}

void DynamicBox::draw(sf::RenderWindow* window)
{
    window->draw(sprite);
}

void DynamicBox::update()
{
    sprite.setPosition(body->GetPosition().x*PPM, body->GetPosition().y*PPM); //update the visible rectangle to match the Box2D representation.
    sprite.setRotation(body->GetAngle() / 3.14 * 180); //body returns the angle in radians, so we need to convert to degrees.
}

void DynamicBox::jump(float power)
{
    body->ApplyLinearImpulse(b2Vec2(0, -power), body->GetPosition());
}
