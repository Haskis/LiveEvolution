#include "plantelement.h"

PlantElement::PlantElement()
{
    _color = QColor(0,0,255,100);
    _radius = 15;
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
    qDebug()<<"????";
    _energy -= 1;
    qDebug()<<_energy;
    // Maybe here should be some kind of limited resources ( for now its unlimited so do nothing)
    ;
}

void PlantElement::handleIntersection(PlantElement* e)
{
    // Do nothing, plants don't compete
    ;
}
