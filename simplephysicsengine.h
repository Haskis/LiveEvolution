#ifndef SIMPLEPHYSICSENGINE_H
#define SIMPLEPHYSICSENGINE_H

#include "physicsengine.h"

class LivingElement;


class SimplePhysicsEngine : public PhysicsEngine
{
public:
    SimplePhysicsEngine();
    virtual void updateEnviroment(Map& map);

private:
    float _suppression;
};

#endif // SIMPLEPHYSICSENGINE_H
