#include "livingelement.h"
#include <QVector2D>
#include <assert.h>
LivingElement::LivingElement(Brain* brain):
    _brain(brain),
    _xVelocity(0),
    _yVelocity(0),
    _aVelocity(0),
    _energy(100)
{
    //In this version assume that bot structure is static
    Motor a;
    a._position = -M_PI/4;
    a._power = 0.0;
    a._rForce = 1.0;
    a._aForce = 0.001;
    _motors.push_back(a);

    a._position = M_PI/4;
    a._power = 0.0;
    a._rForce = 1.0;
    a._aForce = -0.001;
    _motors.push_back(std::move(a));


    Sensor s;
    s._position = 0;
    s._range = 25;
    _sensors.push_back(s);
    s._position = M_PI/7;
    s._range = 25;
    _sensors.push_back(s);
    s._position = -M_PI/7;
    s._range = 25;
    _sensors.push_back(s);
    s._position = M_PI/4;
    s._range = 25;
    _sensors.push_back(s);
    s._position = -M_PI/4;
    s._range = 25;
    _sensors.push_back(s);
    s._position = M_PI;
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

float LivingElement::energy() const{
    return _energy;
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


void LivingElement::checkoutEnviroment(Map& map){

    //Use energy to checkoutEnviroment
    _energy -= 0.05;

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

    const std::vector<PlantElement*> food = map.getFoodElements();

    //Reset sensor data
    for(Sensor& sensor: _sensors){
        sensor._color = QColor(0,0,0);
    }

    //For each animal check if he's in range
    for(LivingElement *animal: animals){
        if(animal == this)
            continue;
        senseElement(animal, max);
    }

    //For each animal check if he's in range
    for(PlantElement *plant: food){

        //Check if other animal is in a square (dimention 2*(max+otherRadius) X 2*(max+ otherRadius)) (fast)
        senseElement((Element*)plant, max);
    }
}

void LivingElement::reactToEnviroment(){
    std::vector<float> input;
    std::vector<float> output;

    //Parse brain input
    for(const Sensor& sensor: _sensors){
        input.push_back(sensor._color.red());
        input.push_back(sensor._color.green());
        input.push_back(sensor._color.blue());
    }
    _brain->think(input, output);

    //Parse brain output (predefined structure)
//TEMP COMMENT    assert(_motors.size() == output.size());

    for(Motor& motor: _motors){
        motor._power = output.back();
        output.pop_back();
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

void LivingElement::senseElement(Element* element, float max)
{
    //Check if other element is in a square (dimention 2*(max+otherRadius) X 2*(max+ otherRadius)) (fast)
    if(abs(_xPosition - element->xPosition()) < (max + element->radius()) &&
       abs(_yPosition - element->yPosition()) < (max + element->radius())){

        //More precise check for each sensor
        for(Sensor& sensor: _sensors){

            bool check = checkIntersection(QVector2D(element->xPosition(), element->yPosition()), element->radius(),
                                           QVector2D(_xPosition, _yPosition),
                                           QVector2D(_xPosition+sin(sensor._position+_rotation)*sensor._range,
                                                     _yPosition+ cos(sensor._position+_rotation)*sensor._range));
            if(check){
                sensor._color = element->color();
            }
        }

        //Check for colision with other elements
        QVector2D cirVec = QVector2D(element->xPosition()-xPosition(),element->yPosition()-yPosition());

        if(cirVec.length()< (_radius + element->radius())){

            // We call element handleIntersection(Element*) which will in turn call
            // our function handleIntersection with correct dynamic type
            element->handleIntersection(this);
        }
    }
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
