#include "simplephysicsengine.h"

#include <element.h>
#include "livingelement.h"
#include <QDebug>
#include <math.h>
#include <algorithm>
SimplePhysicsEngine::SimplePhysicsEngine():
    _suppression(0.1f)
{
}

void SimplePhysicsEngine::updateEnviroment(Map& map)
{
    for(LivingElement* animal : map.getAnimalElemensts()){

        // Update animal velocity based on motors power
        for(const LivingElement::Motor& motor: animal->getMotors() ){
            float motorAngle = animal->rotation()+motor._position;
            // We dont use moment of interia or mass, (assume mass == 1, moment == 1)
            animal->setXVelocity(animal->xVelocity()+(motor._rForce*motor._power)*sin(motorAngle));

            animal->setYVelocity(animal->yVelocity()+(motor._rForce*motor._power)*cos(motorAngle));
            animal->setAVelocity(animal->aVelocity()+(motor._aForce*motor._power));

        }
        // Apply suppression ( simple )

        float xVel = animal->xVelocity();
        float xVelS = xVel*xVel;
        float yVel = animal->yVelocity();
        float yVelS = yVel*yVel;
        float aVel = animal->aVelocity();
        float aVelS = aVel*aVel;

        if(xVel<0){
            animal->setXVelocity(std::min(xVel+_suppression*xVelS, 0.0f));
        }
        else if(xVel>0){
            animal->setXVelocity(std::max(xVel-_suppression*xVelS, 0.0f));
        }
        if(yVel<0){
            animal->setYVelocity(std::min(yVel+_suppression*yVelS, 0.0f));
        }
        else if(yVel>0){
            animal->setYVelocity(std::max(yVel-_suppression*yVelS, 0.0f));
        }
        if(aVel<0){
            animal->setAVelocity(std::min(aVel+_suppression*10*aVelS, 0.0f));
        }
        else if(aVel>0){
            animal->setAVelocity(std::max(aVel-_suppression*10*aVelS, 0.0f));
        }

        animal->setXPosition(animal->xPosition()+animal->xVelocity());
        animal->setYPosition(animal->yPosition()+animal->yVelocity());
        animal->setRotation(animal->rotation()+animal->aVelocity());

//        if(animal->getCollidingElements().size() != 0){
//            //qDebug()<<"Coliding"<<animal->getCollidingElements().size();
//            animal->setXVelocity(-animal->xVelocity());

//            animal->setYVelocity(-animal->yVelocity());
//            animal->clearColidingElements();
//        }


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
