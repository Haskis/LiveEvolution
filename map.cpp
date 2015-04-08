#include "map.h"
#include <livingelement.h>
Map::Map(int xSize, int ySize):
    QObject(nullptr)
{
    _xSize = xSize;
    _ySize = ySize;
}

void Map::addFood(PlantElement* food){
    _foodElements.push_back(food);
}

void Map::addAnimal(LivingElement* element){
    _populationElements.push_back(element);
}

void Map::logPopulation()
{

}

const std::vector<PlantElement*>& Map::getFoodElements(){
    return _foodElements;
}

const std::vector<LivingElement*>& Map::getAnimalElemensts(){
    return _populationElements;
}

QRect Map::boundingRect(){
    return QRect(0,0, _xSize,_ySize);
}

void Map::cleanDead(){
    //std::remove_if(_populationElements.begin(),_populationElements.end(),[](LivingElement* e){return e->energy()<0; });

    for (auto it = _populationElements.begin(); it != _populationElements.end() /* not hoisted */; /* no increment */)
    {
        if ((*it)->energy()<0)
        {
            delete *it;
            _populationElements.erase(it);
            qDebug()<<"DELETED";
            confirmStructureChanges();
        }
        else
        {
            ++it;
        }
    }
}

void Map::confirmValueChanges(){
    emit valuesChanged();
}

void Map::confirmStructureChanges(){
    emit structureChanged();
}
