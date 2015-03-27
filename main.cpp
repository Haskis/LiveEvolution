#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include <simulation.h>

#include <element.h>
#include "map.h"
#include <plantelement.h>
#include <meateater.h>
#include "planteater.h"
#include "annbrain.h"

#include <mapview.h>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    qmlRegisterType<MapView>("ZPR", 1, 0, "MapView");
    QString reason;
    qmlRegisterUncreatableType<Map>("ZPR", 1, 0, "Map",reason);

    // Create map 1000x1000
    Map *map = new Map(800, 400);

    //Add food in a random way
    for(int i=0; i< 0; i++){
        Element* elem = new PlantElement;

        elem->setRandomPosition(map->boundingRect());

        map->addFood(elem);
    }

    //Add MeatEaters in a random way
    for(int i=0; i<10; i++){
        LivingElement* lElem = new MeatEater(new ANNBrain);

        lElem->setRandomPosition(map->boundingRect());
//        lElem->setXPosition(750);
//        lElem->setYPosition(350);
        map->addAnimal(lElem);
    }

    //Add PlantEaters in a random way
    for(int i=0; i<10; i++){
        LivingElement* lElem = new PlantEater(new ANNBrain);

        lElem->setRandomPosition(map->boundingRect());
//        lElem->setXPosition(720);
//        lElem->setYPosition(320);
        map->addAnimal(lElem);
    }

    //Create mutator for evolution purpouses, physicsEngine to simulate objects movement
    Mutator *mutator = new BasicMutator;
    PhysicsEngine *pEngine = new SimplePhysicsEngine;

    //Create simulation object, when simulation starts loop begins
    Simulation simulation(map, mutator, pEngine);

    // Starts simulation, after each iteration condition for cycle end is checked
    // If cycle ends new population is created based on old population and new cycle runs
    // from begining
    simulation.start();

    qDebug()<<map->getAnimalElemensts().size();

    return app.exec();
}
