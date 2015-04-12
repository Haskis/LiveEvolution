#ifndef MEATEATER_H
#define MEATEATER_H

#include "livingelement.h"
#include "element.h"
#include "meateater.h"
#include "planteater.h"
#include "plantelement.h"

class MeatEater : public LivingElement
{
public:

    MeatEater(Brain* brain);
    virtual ~MeatEater();

    virtual Type type() const ;

    //Inherited from Element
    virtual void handleIntersection(Element *e);
    virtual void handleIntersection(MeatEater *e);
    virtual void handleIntersection(PlantEater *e);
    virtual void handleIntersection(PlantElement *e);
};

#endif // MEATEATER_H
