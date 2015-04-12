#ifndef FOODNODE_H
#define FOODNODE_H

#include "basenode.h"
#include "plantelement.h"

class FoodNode : public BaseNode
{

public:
    explicit FoodNode(PlantElement *element);

    virtual void updateGeometry();

private:

    PlantElement* m_pElement;
};

#endif // ANIMALNODE_H
