#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "map.h"

class PhysicsEngine
{
public:
    PhysicsEngine();
    virtual ~PhysicsEngine();
    virtual void updateEnviroment(Map& map) = 0;
};

#endif // PHYSICSENGINE_H
