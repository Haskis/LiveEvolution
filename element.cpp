#include "element.h"
#include <QDebug>
Element::Element():
    _xPosition(0),
    _yPosition(0),
    _radius(3),
    _rotation(0),
    _color(Qt::red),
    _selected(false),
    _energy(100)
{

}

Element::~Element()
{

}

QColor Element::color() const{
    return _color;
}

void Element::setColor(const QColor& color){
    _color = color;
}

bool Element::selected() const{
    return _selected;
}

float Element::energy() const{
    return _energy;
}

void Element::resetEnergy(){
    _energy = 100;
}

void Element::setSelected(bool selected){
    _selected = selected;
}

float Element::radius() const{
    return _radius;
}

void Element::setRadius(float radius){
    _radius = radius;
}

float Element::rotation() const{
    return _rotation;
}

void Element::setRotation(float rotation){
    _rotation = rotation;
}

float Element::xPosition() const{
    return _xPosition;
}

float Element::yPosition() const{
    return _yPosition;
}

void Element::setXPosition(float xPosition){
    _xPosition = xPosition;
}

void Element::setYPosition(float yPosition){
    _yPosition = yPosition;
}

void Element::setRandomPosition(const QRect& rect){
    _xPosition = rect.x() + (float)rand()*(rect.width())/RAND_MAX;
    _yPosition = rect.y() + (float)rand()*(rect.height())/RAND_MAX;

}

void Element::clearColidingElements(){
    _collidingElements.clear();
}

const std::vector<const Element*> Element::getCollidingElements(){
    return _collidingElements;
}
