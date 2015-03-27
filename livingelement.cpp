#include "livingelement.h"
#include <QVector2D>
#include <assert.h>
LivingElement::LivingElement(Brain* brain):
    _brain(brain),
    _xVelocity(-0.5),
    _yVelocity(-0.5),
    _aVelocity(0),
    _mass(1)
{
    Motor a;
    a._position = 0;
    a._power = 0.05;
    a._rForce = 1;
    a._aForce = 0.001;
    _motors.push_back(a);
    a._position = 3.15;
    a._power = 0.003;
    a._rForce = 1;
    a._aForce = 1;
    _motors.push_back(std::move(a));

    Sensor s;
    s._position = 0;
    s._range = 25;
    _sensors.push_back(s);
    s._position = M_PI/2;
    s._range = 25;
    _sensors.push_back(s);
    s._position = M_PI;
    s._range = 25;
    _sensors.push_back(s);
    s._position = M_PI/2+M_PI;
    s._range = 25;
    _sensors.push_back(std::move(s));
}

LivingElement::~LivingElement()
{

}

float LivingElement::xVelocity() const{
    return _xVelocity;
}

float LivingElement::yVelocity() const{
    return _yVelocity;
}

float LivingElement::aVelocity() const{
    return _aVelocity;
}

void LivingElement::setXVelocity(float velocity){
    if(_xVelocity != velocity){
        _xVelocity = velocity;
    }
}

void LivingElement::setYVelocity(float velocity){
    if(_yVelocity != velocity){
        _yVelocity = velocity;
    }
}

void LivingElement::setAVelocity(float velocity){
    if(_aVelocity != velocity){
        _aVelocity = velocity;
    }
}

float LivingElement::mass() const{
    return _mass;
}

void LivingElement::checkoutEnviroment(Map& map){

    //Find how far this animal can see from his centre
    float max = 0;
    for(Sensor sensor: _sensors){
        if(sensor._range>max){
            max = sensor._range;
        }
        sensor._color = QColor(0,0,0);
    }

    //Get table of all animals in enviroment
    const std::vector<LivingElement*> animals = map.getAnimalElemensts();

    //For each animal check if he's in range

    for(Sensor& sensor: _sensors){
        sensor._color = QColor(0,0,0);
    }

    for(LivingElement *animal: animals){
        if(animal == this)
            continue;
        //Check if other animal is in a square (dimention 2*(max+otherRadius) X 2*(max+ otherRadius)) (fast)
        if(abs(_xPosition - animal->_xPosition) < (max + animal->_radius) &&
           abs(_yPosition - animal->_yPosition) < (max + animal->_radius)){

            //More precise check for each sensor

            for(Sensor& sensor: _sensors){


                bool check = checkIntersection(QVector2D(animal->_xPosition, animal->_yPosition), animal->_radius,
                                               QVector2D(_xPosition, _yPosition),
                                               QVector2D(_xPosition+sin(sensor._position+_rotation)*sensor._range,
                                                         _yPosition+ cos(sensor._position+_rotation)*sensor._range));
                if(check){
                    sensor._color = animal->_color;
                }
            }


            //Check for colision
//            if(cirVecLength< (_radius + animal->_radius)){

//                // We call animal handleIntersection(Element*) which will in turn call
//                // our function handleIntersection with correct dynamic type
//                animal->handleIntersection(this);
//            }
        }
    }
}

void LivingElement::reactToEnviroment(){
    std::vector<float> input;
    std::vector<float> output;

    //Parse brain input
    for(Sensor sensor: _sensors){
        input.push_back(sensor._color.red());
        input.push_back(sensor._color.green());
        input.push_back(sensor._color.blue());
    }
    _brain->think(input, output);

    //Parse brain output (predefined structure)
//TEMP COMMENT    assert(_motors.size() == output.size());

    for(Motor motor: _motors){
//TEMP COMMENT        motor._power = output.back();
        motor._power =0.5;
//TEMP COMMENT        output.pop_back();
    }
}

std::vector<float> LivingElement::structureGene() const
{

}

std::vector<float> LivingElement::behaviourGene() const
{

}

void LivingElement::updateStructure(const std::vector<float>& gene)
{

}

void LivingElement::updateBehaviour(const std::vector<float>* gene)
{

}

const std::vector<LivingElement::Sensor> LivingElement::getSensors() const{
    return _sensors;
}

const std::vector<LivingElement::Motor> LivingElement::getMotors() const{
    return _motors;
}

bool LivingElement::checkIntersection(QVector2D circleCentre, float circleRadius, QVector2D segmentBegin, QVector2D segmentEnd)
{
    QVector2D beginToCentre = circleCentre - segmentBegin;
    QVector2D segment = segmentEnd - segmentBegin;
    float dotProduct = QVector2D::dotProduct(beginToCentre, segment);
    float val = dotProduct/(segment.x()*segment.x() + segment.y() *segment.y());
    QVector2D closestPoint;
    if(val < 0)
        closestPoint = segmentBegin;
    else if (val >1)
        closestPoint = segmentEnd;
    else
        closestPoint = val*segment + segmentBegin;

    if((closestPoint-circleCentre).length()>circleRadius)
        return false;
    else
        return true;
}


LivingElement::Sensor::Sensor():
    _color(QColor(0,0,0)),
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
