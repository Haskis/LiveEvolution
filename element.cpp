#include "element.h"

#include <QDebug>

Element::Element():
    m_selected(false),
    m_energy(100),
    m_xPosition(0),
    m_yPosition(0),
    m_radius(3),
    m_rotation(0),
    m_color(Qt::red)
{


}

Element::~Element()
{

}

QColor Element::color() const{
    return m_color;
}

void Element::setColor(const QColor& color){
    m_color = color;
}

bool Element::selected() const{
    return m_selected;
}

float Element::energy() const{
    return m_energy;
}

void Element::resetEnergy(){
    m_energy = 100;
}

void Element::setSelected(bool selected){
    m_selected = selected;
}

float Element::radius() const{
    return m_radius;
}

void Element::setRadius(float radius){
    m_radius = radius;
}

float Element::rotation() const{
    return m_rotation;
}

void Element::setRotation(float rotation){
    m_rotation = rotation;
}

float Element::xPosition() const{
    return m_xPosition;
}

float Element::yPosition() const{
    return m_yPosition;
}

void Element::setXPosition(float xPosition){
    m_xPosition = xPosition;
}

void Element::setYPosition(float yPosition){
    m_yPosition = yPosition;
}

void Element::setRandomPosition(const QRect& rect){

    m_xPosition = rect.x() + (float)rand()*(rect.width())/RAND_MAX;
    m_yPosition = rect.y() + (float)rand()*(rect.height())/RAND_MAX;

}

void Element::clearColidingElements(){
    m_collidingElements.clear();
}

const std::vector<const Element*> Element::getCollidingElements(){
    return m_collidingElements;
}
