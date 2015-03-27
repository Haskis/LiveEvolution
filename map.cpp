#include "map.h"
#include <QtQml>

#include <QQmlApplicationEngine>
#include <QSurfaceFormat>
#include <QQuickWindow>
Map::Map(int xSize, int ySize):
    QObject(nullptr)
{
    _xSize = xSize;
    _ySize = ySize;

    engine = new QQmlApplicationEngine;

    engine->rootContext()->setContextProperty("mapa", this);
    //engine->rootContext()->setContextProperty("food", _food);

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *topLevel = engine->rootObjects()[0];
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
    QSurfaceFormat format = window->format();
    format.setSamples(16);
    window->setFormat(format);
}

void Map::addFood(Element* food){
    _foodElements.push_back(food);
}

void Map::addAnimal(LivingElement* element){
    _populationElements.push_back(element);
}

void Map::logPopulation()
{

}

const std::vector<Element*>& Map::getFoodElements(){
    return _foodElements;
}

const std::vector<LivingElement*>& Map::getAnimalElemensts(){
    return _populationElements;
}

QRect Map::boundingRect(){
    return QRect(0,0, _xSize,_ySize);
}

void Map::confirmValueChanges()
{
    emit valuesChanged();
}

void Map::confirmStructoreChanges()
{

}
