#ifndef MAP_H
#define MAP_H


class Element;
class LivingElement;

class Population;
class Food;

#include <vector>
#include <QRect>

class Map
{

public:
    explicit Map(float xSize, float ySize);

    //For logic

    void addFood(Element* food);
    void addAnimal(LivingElement*element);
    void logPopulation();
    void setNewPopulation(Population *);
    const std::vector<Element*>& getFoodElements();
    const std::vector<LivingElement*>& getAnimalElemensts();

    QRect boundingRect();

private:

    float _xSize;
    float _ySize;

    Food* _food;
    Population* _population;

};

#endif // MAP_H
