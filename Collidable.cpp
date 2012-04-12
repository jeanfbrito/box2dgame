#include "Collidable.h"

Collidable::Collidable(const std::string& name) : name(name)
{
    //ctor
}

Collidable::~Collidable()
{
    //dtor
}

std::string Collidable::getName() const
{
    return name;
}

bool Collidable::isAwake()
{
    if(body->GetLinearVelocity().x < 0.005 && body->GetLinearVelocity().y < 0.005)
    {
        //stabilize();
        body->SetLinearVelocity(b2Vec2(0, 0));
        return false;
    }
    return true;
}

b2Body* Collidable::getBody()
{
    return body;
}

void Collidable::stabilize()
{
    if(std::abs(body->GetAngle()) < 0.03)
        body->SetTransform(body->GetPosition(), 0);
}
