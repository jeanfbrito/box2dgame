#include "ContactListener.h"

ContactListener::ContactListener()
{
    //ctor
}

ContactListener::~ContactListener()
{
    //dtor
}

void ContactListener::BeginContact(b2Contact* contact)
{
    Collidable* colA = (Collidable*)contact->GetFixtureA()->GetBody()->GetUserData();
    Collidable* colB = (Collidable*)contact->GetFixtureB()->GetBody()->GetUserData();

    if(colA != NULL && colB != NULL)
    {
        colA->onCollisionBegin(colB->getName(), contact);
        colB->onCollisionBegin(colA->getName(), contact);
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    Collidable* colA = (Collidable*)contact->GetFixtureA()->GetBody()->GetUserData();
    Collidable* colB = (Collidable*)contact->GetFixtureB()->GetBody()->GetUserData();

    if(colA != NULL && colB != NULL)
    {
        colA->onCollisionEnd(colB->getName(), contact);
        colB->onCollisionEnd(colA->getName(), contact);
    }
}

void ContactListener::PreSolve (b2Contact *contact, const b2Manifold *oldManifold)
{
    Collidable* colA = (Collidable*)contact->GetFixtureA()->GetBody()->GetUserData();
    Collidable* colB = (Collidable*)contact->GetFixtureB()->GetBody()->GetUserData();

    if(colA != NULL)
        colA->preSolve(contact, oldManifold);
    if(colB != NULL)
        colB->preSolve(contact, oldManifold);
}
void ContactListener::PostSolve (b2Contact *contact, const b2ContactImpulse *impulse)
{
    Collidable* colA = (Collidable*)contact->GetFixtureA()->GetBody()->GetUserData();
    Collidable* colB = (Collidable*)contact->GetFixtureB()->GetBody()->GetUserData();

    if(colA != NULL)
        colA->postSolve(contact, impulse);
    if(colB != NULL)
        colB->postSolve(contact, impulse);
}
