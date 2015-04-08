#include "plantelement.h"

PlantElement::PlantElement()
{
    _color = QColor(Qt::blue);
}

PlantElement::~PlantElement()
{

}

void PlantElement::handleIntersection(Element* e)
{
    e->handleIntersection(this);
}

void PlantElement::handleIntersection(MeatEater* e)
{
    // Do nothing
    ;
}

void PlantElement::handleIntersection(PlantEater* e)
{
    // Maybe here should be some kind of limited resources ( for now its unlimited so do nothing)
    ;
}

void PlantElement::handleIntersection(PlantElement* e)
{
    // Do nothing, plants don't compete
    ;
}
