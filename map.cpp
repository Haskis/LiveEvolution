#include "map.h"

#include "livingelement.h"
#include "plantelement.h"
#include "basicmutator.h"

Map::Map(int xSize, int ySize):
    QObject(nullptr)
{
    m_xSize = xSize;
    m_ySize = ySize;
}

Map::~Map()
{
    for(auto elem: m_populationElements)
        delete elem;
    for(auto elem: m_foodElements)
        delete elem;
}

void Map::addFood(PlantElement* food){
    m_foodElements.push_back(food);
}

void Map::addAnimal(LivingElement* element){
    m_populationElements.push_back(element);
}

const std::vector<PlantElement*>& Map::getFoodElements(){
    return m_foodElements;
}

const std::vector<LivingElement*>& Map::getAnimalElemensts(){
    return m_populationElements;
}

QRect Map::boundingRect(){
    return QRect(0,0, m_xSize,m_ySize);
}

void Map::cleanDead(Mutator *mutator){
    //std::remove_if(_populationElements.begin(),_populationElements.end(),[](LivingElement* e){return e->energy()<0; });

    // Search for elements with energy less than 0
    for (auto it = m_populationElements.begin(); it != m_populationElements.end(); it++){

        if ((*it)->energy()<0){
            std::vector<LivingElement*> sameType;
            // Find all elements of the same type in this population (but not itself)
            for (auto ite = m_populationElements.begin(); ite != m_populationElements.end(); ite++){
                if((*it)->type() == (*ite)->type() && (*it) != (*ite)){
                    sameType.push_back(*ite);
                }
            }
            // Let mutator change this dead animal gene, then "ressurect" it
            mutator->mutate(sameType, (*it));
            (*it)->setRandomPosition(boundingRect());
            (*it)->resetEnergy();
        }
    }

    for (auto it = m_foodElements.begin(); it != m_foodElements.end() /* not hoisted */; /* no increment */)
    {
        if ((*it)->energy()<0)
        {
            (*it)->setRandomPosition(boundingRect());
            (*it)->resetEnergy();
        }
        ++it;

    }
}

void Map::confirmValueChanges(){
    emit valuesChanged();
}

void Map::confirmStructureChanges(){
    emit structureChanged();
}
