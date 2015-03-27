#include "simplephysicsengine.h"

#include <element.h>
#include "livingelement.h"
#include <QDebug>
SimplePhysicsEngine::SimplePhysicsEngine():
    _suppression(0.5)
{
}

void SimplePhysicsEngine::updateEnviroment(Map& map)
{
    for(LivingElement* animal : map.getAnimalElemensts()){
        //update animal velocity based on power
        for(const LivingElement::Motor& motor: animal->getMotors() ){
            float motorAngle = animal->rotation()+motor._position;
            //qDebug()<<"Power"<<motor._power;
            animal->setXVelocity(animal->xVelocity()+(motor._rForce*motor._power/animal->mass())*sin(motorAngle));
            animal->setYVelocity(animal->yVelocity()+(motor._rForce*motor._power/animal->mass())*cos(motorAngle));
            animal->setAVelocity(animal->aVelocity()+(motor._aForce*motor._power));
        }
        //qDebug()<<"VEL"<<animal->xVelocity();
        //Update animal position based on velocity
        if(animal->getCollidingElements().size() == 0){
            animal->setXPosition(animal->xPosition()+animal->xVelocity());
            animal->setYPosition(animal->yPosition()+animal->yVelocity());
            animal->setRotation(animal->rotation()+animal->aVelocity());
        }

        //Check boundaries
        if(animal->xPosition()<animal->radius())
            animal->setXPosition(animal->radius());
        else if(animal->xPosition()> map.boundingRect().width()-animal->radius())
            animal->setXPosition(map.boundingRect().width()-animal->radius());
        if(animal->yPosition()<animal->radius())
            animal->setYPosition(animal->radius());
        else if(animal->yPosition()>map.boundingRect().height()-animal->radius())
            animal->setYPosition(map.boundingRect().height()-animal->radius());

    }
    map.confirmValueChanges();
}
