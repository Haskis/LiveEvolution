#ifndef PLANTEATER_H
#define PLANTEATER_H



#include "livingelement.h"
#include "element.h"
#include "meateater.h"
#include "planteater.h"
#include "plantelement.h"


class PlantEater : public LivingElement
{
public:
    PlantEater(Brain* brain);
    virtual ~PlantEater();

    //Inherited from Element
    virtual void handleIntersection(Element *e);
    virtual void handleIntersection(MeatEater *e);
    virtual void handleIntersection(PlantEater *e);
    virtual void handleIntersection(PlantElement *e);


};

#endif // PLANTEATER_H
