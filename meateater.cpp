#include "meateater.h"

MeatEater::MeatEater(Brain* brain):
    LivingElement(brain)
{
    m_color = QColor(255,0,0,10);
}

MeatEater::~MeatEater()
{

}

LivingElement::Type MeatEater::type() const{
    return MEAT_EATER;
}

void MeatEater::handleIntersection(Element* e){
    e->handleIntersection(this);
}

void MeatEater::handleIntersection(PlantElement* e){
    Q_UNUSED(e);
    //Ignore
}

void MeatEater::handleIntersection(PlantEater* e){
    Q_UNUSED(e);
    m_energy += 0.2;
}

void MeatEater::handleIntersection(MeatEater* e){
    m_collidingElements.push_back(e);
}
