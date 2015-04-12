#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QSurfaceFormat>
#include <QQuickWindow>

#include "simulation.h"
#include "element.h"
#include "map.h"
#include "plantelement.h"
#include "meateater.h"
#include "planteater.h"
#include "annbrain.h"
#include "mapview.h"

const int mapXSize = 800;
const int mapYSize = 600;

const int nFood = 15;
const int nMeatE = 15;
const int nPlantE = 15;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Register types for QML View
    qmlRegisterType<SelectedElementData>("ZPR", 1, 0, "SelectedElementData");
    qmlRegisterType<MapView>("ZPR", 1, 0, "MapView");
    QString reason;
    qmlRegisterUncreatableType<Map>("ZPR", 1, 0, "Map",reason);

    // Create map if predefined size
    Map *map = new Map(mapXSize, mapYSize);

    //Add food in a random way
    for(int i=0; i<nFood; i++){
        PlantElement* elem = new PlantElement;
        elem->setRandomPosition(map->boundingRect());
        map->addFood(elem);
    }

    //Add MeatEaters in a random way
    for(int i=0; i<nMeatE; i++){
        LivingElement* lElem = new MeatEater(new ANNBrain);

        lElem->setRandomPosition(map->boundingRect());
        map->addAnimal(lElem);
    }

    //Add PlantEaters in a random way
    for(int i=0; i<nPlantE; i++){
        LivingElement* lElem = new PlantEater(new ANNBrain);

        lElem->setRandomPosition(map->boundingRect());
        map->addAnimal(lElem);
    }

    //Create mutator for evolution purpouses, physicsEngine to simulate objects movement
    Mutator *mutator = new BasicMutator;
    PhysicsEngine *pEngine = new SimplePhysicsEngine;

    //Create simulation object, it should be started when ready
    Simulation simulation(map, mutator, pEngine);

    //Qml View
    QQmlApplicationEngine* engine;
    engine = new QQmlApplicationEngine;

    engine->rootContext()->setContextProperty("mapa", map);
    engine->rootContext()->setContextProperty("simulation", &simulation);

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));

    //Set antialiasing
    QObject *topLevel = engine->rootObjects()[0];
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
    QSurfaceFormat format = window->format();
    format.setSamples(16);
    window->setFormat(format);

    return app.exec();
}
