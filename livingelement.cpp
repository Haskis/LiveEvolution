#include "livingelement.h"

LivingElement::LivingElement(Brain* brain)
{
}

std::vector<float> LivingElement::structoreGene() const
{

}


LivingElement::Sensor::Sensor():
    _r(false),
    _g(false),
    _b(false),
    _position(0),
    _range(1)
{

}


LivingElement::Motor::Motor():
    _position(0),
    _aForce(0),
    _rForce(0),
    _power(0)
{

}
