#ifndef COLLIDABLE_H
#define COLLIDABLE_H
#include <Box2D/Box2D.h>

class Collidable
{
    public:
        Collidable(const std::string& name);
        virtual ~Collidable();

        virtual void update(){}; //static objects won't need it.

        virtual void onCollisionBegin(const std::string& object, b2Contact* contact){}
        virtual void onCollisionEnd(const std::string& object, b2Contact* contact){}
        virtual void postSolve (b2Contact *contact, const b2ContactImpulse *impulse){}
        virtual void preSolve (b2Contact *contact, const b2Manifold *oldManifold){}

        std::string getName() const;
        void stabilize();
        bool isAwake();
        b2Body* getBody();

    protected:
        b2Body* body;
        std::string name;

};

#endif // COLLIDABLE_H
