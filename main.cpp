#include <QApplication>
#include <QQmlApplicationEngine>

#include <simulation.h>

#include <element.h>
#include "map.h"
#include <plantelement.h>
#include <meateater.h>
#include "planteater.h"
#include "annbrain.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // Create map 1000x1000
    Map *map = new Map(1000, 1000);

    //Add food in a random way
    for(int i=0; i< 100; i++){
        Element* elem = new PlantElement;

        elem->setRandomPosition(map->boundingRect());
        map->addFood(elem);
    }

    //Add MeatEaters in a random way
    for(int i=0; i<20; i++){
        LivingElement* lElem = new MeatEater(new ANNBrain);

        lElem->setRandomPosition(map->boundingRect());
        map->addAnimal(lElem);
    }

    //Add PlantEaters in a random way
    for(int i=0; i<20; i++){
        LivingElement* lElem = new PlantEater(new ANNBrain);

        lElem->setRandomPosition(map->boundingRect());
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


    return app.exec();
}
