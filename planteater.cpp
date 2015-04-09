#include "planteater.h"

PlantEater::PlantEater(Brain *brain):
    LivingElement(brain)
{
    _color = QColor(Qt::green);
}

PlantEater::~PlantEater()
{

}

void PlantEater::handleIntersection(Element* e)
{
   //qDebug()<<"Handling intersection in PlantEater";
    e->handleIntersection(this);
}

void PlantEater::handleIntersection(MeatEater* e)
{
    _energy -= 0.1;
    //qDebug()<<_energy;
}

void PlantEater::handleIntersection(PlantElement* e)
{
    _energy += 0.2;
}

void PlantEater::handleIntersection(PlantEater* e)
{
    _collidingElements.push_back(e);
}
