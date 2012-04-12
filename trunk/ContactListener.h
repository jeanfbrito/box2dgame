#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H
#include "Collidable.h"
#include <Box2D/Box2D.h>


class ContactListener : public b2ContactListener
{
    public:
        ContactListener();
        virtual ~ContactListener();
        void 	BeginContact (b2Contact *contact);
        void 	EndContact (b2Contact *contact);

        void 	PreSolve (b2Contact *contact, const b2Manifold *oldManifold);
        void 	PostSolve (b2Contact *contact, const b2ContactImpulse *impulse);
    private:
};

#endif // CONTACTLISTENER_H
