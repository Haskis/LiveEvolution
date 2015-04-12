#include "planteater.h"

PlantEater::PlantEater(Brain *brain):
    LivingElement(brain)
{
    m_color = QColor(Qt::green);
}

PlantEater::~PlantEater()
{

}

LivingElement::Type PlantEater::type() const{
    return PLANT_EATER;
}

void PlantEater::handleIntersection(Element* e){
    e->handleIntersection(this);
}


void PlantEater::handleIntersection(MeatEater* e){
    Q_UNUSED(e);
    m_energy -= 0.1;

}

void PlantEater::handleIntersection(PlantElement* e){
    m_energy += 0.2;
    e->handleIntersection(this);
}

void PlantEater::handleIntersection(PlantEater* e){
    m_collidingElements.push_back(e);
}
