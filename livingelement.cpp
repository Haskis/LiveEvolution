#include "livingelement.h"

#include <QVector2D>
#include <assert.h>

#ifndef M_PI
#define M_PI 3.14
#endif

LivingElement::LivingElement(Brain* brain):
    m_xVelocity(0),
    m_yVelocity(0),
    m_aVelocity(0),
    m_brain(brain)
{
    //In this version assume that bot structure is static
    Motor a;
    a._position = -M_PI/4;
    a._power = 0.0;
    a._rForce = 0.1;
    a._aForce = 0.00005;
    m_motors.push_back(a);

    a._position = M_PI/4;
    a._power = 0.0;
    a._rForce = 0.1;
    a._aForce = -0.00005;
    m_motors.push_back(std::move(a));


    Sensor s;

    s._position = M_PI/4;
    s._range = 50;
    m_sensors.push_back(s);

    s._position = -M_PI/4;
    s._range = 50;
    m_sensors.push_back(s);


    s._position = M_PI/100;
    s._range = 120;
    m_sensors.push_back(s);

    s._position = -M_PI/100;
    s._range = 120;
    m_sensors.push_back(s);

    s._position = M_PI/10;
    s._range = 35;
    m_sensors.push_back(s);

    s._position = -M_PI/10;
    s._range = 35;
    m_sensors.push_back(std::move(s));
}

LivingElement::~LivingElement()
{
    delete m_brain;

}

float LivingElement::xVelocity() const{
    return m_xVelocity;
}

float LivingElement::yVelocity() const{
    return m_yVelocity;
}

float LivingElement::aVelocity() const{
    return m_aVelocity;
}


void LivingElement::setXVelocity(float velocity){
    if(m_xVelocity != velocity){
        m_xVelocity = velocity;
    }
}

void LivingElement::setYVelocity(float velocity){
    if(m_yVelocity != velocity){
        m_yVelocity = velocity;
    }
}

void LivingElement::setAVelocity(float velocity){
    if(m_aVelocity != velocity){
        m_aVelocity = velocity;
    }
}


void LivingElement::checkoutEnviroment(Map& map){

    //Use energy to checkoutEnviroment
    m_energy -= 0.05;

    //Find how far this animal can see from his centre
    float max = 0;
    for(Sensor sensor: m_sensors){
        if(sensor._range>max){
            max = sensor._range;
        }
        sensor._color = QColor(0,0,0);
    }

    //Get table of all animals in enviroment
    const std::vector<LivingElement*> animals = map.getAnimalElemensts();

    const std::vector<PlantElement*> food = map.getFoodElements();

    //Reset sensor data
    for(Sensor& sensor: m_sensors){
        sensor._color = QColor(0,0,0);
    }

    //For each animal check if he's in range
    for(LivingElement *animal: animals){
        if(animal == this)
            continue;
        senseElement((Element*)animal, max);
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
    for(const Sensor& sensor: m_sensors){
        input.push_back(sensor._color.red()/255.0f);
        input.push_back(sensor._color.green()/255.0f);
        input.push_back(sensor._color.blue()/255.0f);
    }
    m_brain->think(input, output);

    for(Motor& motor: m_motors){
        motor._power = output.back();
        output.pop_back();
    }
}

//const std::vector<float>& LivingElement::structureGene() const
//{

//    //Currently does nothing (not used)
//}

const std::vector<float>& LivingElement::behaviourGene() const{
    return m_brain->gene();
}

//void LivingElement::updateStructure(const std::vector<float>& gene)
//{
//    //Currently does nothing (not used)
//}

void LivingElement::updateBehaviour(const std::vector<float>& gene){
    m_brain->updateGene(gene);
}

const std::vector<LivingElement::Sensor>& LivingElement::getSensors() const{
    return m_sensors;
}

const std::vector<LivingElement::Motor>& LivingElement::getMotors() const{
    return m_motors;
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
    if(abs(m_xPosition - element->xPosition()) < (max + element->radius()) &&
       abs(m_yPosition - element->yPosition()) < (max + element->radius())){

        //More precise check for each sensor
        for(Sensor& sensor: m_sensors){

            bool check = checkIntersection(QVector2D(element->xPosition(), element->yPosition()), element->radius(),
                                           QVector2D(m_xPosition, m_yPosition),
                                           QVector2D(m_xPosition+sin(sensor._position+m_rotation)*sensor._range,
                                                     m_yPosition+ cos(sensor._position+m_rotation)*sensor._range));
            if(check){
                sensor._color = element->color();
            }
        }

        //Check for colision with other elements
        QVector2D cirVec = QVector2D(element->xPosition()-xPosition(),element->yPosition()-yPosition());

        if(cirVec.length()< (m_radius + element->radius())){

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
