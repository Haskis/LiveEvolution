#include "plantelement.h"

PlantElement::PlantElement()
{
    m_color = QColor(0,0,255,100);
    m_radius = 15;
}

PlantElement::~PlantElement()
{

}

void PlantElement::handleIntersection(Element* e){
    e->handleIntersection(this);
}

void PlantElement::handleIntersection(MeatEater* e){
    Q_UNUSED(e);
}

void PlantElement::handleIntersection(PlantEater* e){
    Q_UNUSED(e);
    m_energy -= 1;
}

void PlantElement::handleIntersection(PlantElement* e)
{
    Q_UNUSED(e);
    //Ignored
}
