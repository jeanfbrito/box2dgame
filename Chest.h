#ifndef CHEST_H
#define CHEST_H
#include "DynamicBox.h"

class Chest : public DynamicBox
{
    public:
        Chest(float x, float y, float rotation, b2World& world);
        ~Chest();

        void postSolve(b2Contact *contact, const b2ContactImpulse *impulse);
        bool isOpen(){return opened;}

    private:
        bool opened;
};

#endif // CHEST_H
