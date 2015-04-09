#ifndef PLANTELEMENT_H
#define PLANTELEMENT_H

#include "livingelement.h"
#include "element.h"
#include "meateater.h"
#include "planteater.h"
#include "plantelement.h"

class PlantElement : public Element
{

public:
    PlantElement();
    virtual ~PlantElement();

    virtual void handleIntersection(Element *e);
    virtual void handleIntersection(MeatEater *e);
    virtual void handleIntersection(PlantEater *e);
    virtual void handleIntersection(PlantElement *e);


protected:



};

#endif // PLANTELEMENT_H
