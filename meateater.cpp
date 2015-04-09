#include "meateater.h"

MeatEater::MeatEater(Brain* brain):
    LivingElement(brain)
{
    _color = QColor(255,0,0,10);
}

MeatEater::~MeatEater()
{

}

void MeatEater::handleIntersection(Element* e)
{
   // qDebug()<<"Handling intersection in meatEater";
    e->handleIntersection(this);

}

void MeatEater::handleIntersection(PlantElement* e){
    //qDebug()<<"MM with Food";

}

void MeatEater::handleIntersection(PlantEater* e)
{
    //qDebug()<<"MM with PE";
    _energy += 0.2;
}

void MeatEater::handleIntersection(MeatEater* e)
{
    _collidingElements.push_back(e);
}
