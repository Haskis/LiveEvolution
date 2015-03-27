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
    //qDebug()<<"PE with ME";
}

void PlantEater::handleIntersection(PlantElement* e)
{
}

void PlantEater::handleIntersection(PlantEater* e)
{
    _collidingElements.push_back(e);
}
