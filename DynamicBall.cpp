#include "DynamicBall.h"

DynamicBall::DynamicBall(float x, float y, float radius, b2World& world) : Collidable("DynamicBall"), flying(false), hit(false)
{
    b2BodyDef DEF;
    b2CircleShape SHAPE;
    b2FixtureDef FIX;

    DEF.position.Set(x/PPM, y/PPM);
    DEF.type = b2_dynamicBody;
    DEF.fixedRotation = true;
    CIRCLE = sf::CircleShape(radius, 20);
    CIRCLE.setOrigin(radius, radius);
    CIRCLE.setFillColor(sf::Color::White);
    CIRCLE.setOutlineColor(sf::Color::Black);
    CIRCLE.setOutlineThickness(1);
    SHAPE.m_radius = radius/PPM;
    body = world.CreateBody(&DEF);
    FIX.shape = &SHAPE;
    FIX.density = .4f;
    FIX.friction = .5f;
    body->CreateFixture(&FIX);
    body->SetActive(false);

    line.setPrimitiveType(sf::Lines);
    line.resize(2);
    body->SetUserData(this);
}

DynamicBall::~DynamicBall()
{
    body->DestroyFixture(body->GetFixtureList());
    body->GetWorld()->DestroyBody(body);
}

void DynamicBall::shoot(float x, float y)
{
    if(!flying)
    {
        flying = true;
        body->SetActive(true);
        b2Vec2 pos = body->GetPosition();
        float X = pos.x*PPM - x;
        float Y = pos.y*PPM - y;
        body->ApplyLinearImpulse(b2Vec2(X/16.f, Y/16.f), body->GetPosition());
    }
}

void DynamicBall::draw(sf::RenderWindow* window)
{
    window->draw(CIRCLE);
    if(!flying)
        window->draw(line);
}

void DynamicBall::update(sf::Vector2i mousePos)
{
    line[0] = sf::Vertex(sf::Vector2f(body->GetPosition().x*PPM, body->GetPosition().y*PPM));
    line[1] = sf::Vertex(sf::Vector2f(mousePos.x, mousePos.y));
    CIRCLE.setPosition(body->GetPosition().x*PPM, body->GetPosition().y*PPM);
    CIRCLE.setRotation(body->GetAngle() / 3.14 * 180);

    if(CIRCLE.getGlobalBounds().top > HEIGHT)
        hit = true;
}

void DynamicBall::onCollisionBegin(const std::string& name, b2Contact* contact)
{
    hit = true;
}

void DynamicBall::onCollisionEnd(const std::string& name, b2Contact* contact)
{

}
