#include "Chest.h"

Chest::Chest(float x, float y, float rotation, b2World& world) : DynamicBox("chest.txt", x, y, rotation, world)
{
    //ctor
}

Chest::~Chest()
{
    //dtor
}

void Chest::postSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    if(name == "chest.txt")
    {
        int32 count = contact->GetManifold()->pointCount;
        float32 maxImpulse = 0.0f;
        for (int32 i = 0; i < count; ++i)
        {
            maxImpulse = b2Max(maxImpulse, impulse->normalImpulses[i]);
        }

        if(maxImpulse > .8f)
        {
            opened = true;
            sprite.setTexture(rm->getTexture("openChest.png"));
        }
    }
}
