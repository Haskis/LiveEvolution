#ifndef MAP_H
#define MAP_H


class Element;
class LivingElement;

class Population;
class Food;

#include <vector>
#include <QRect>
#include <QObject>

class QQmlApplicationEngine;

class Map: public QObject
{
    Q_OBJECT

public:
    explicit Map(int xSize, int ySize);

    //For logic

    ///
    /// \brief addFood adds food into Food internal container
    /// \param food food element to be added
    ///
    /// Adds food element into Food object container. Food elements
    /// can be accessed using getFoodElements() function
    void addFood(Element* food);

    ///
    /// \brief addAnimal adds animal into Population internal container
    /// \param element animal element to be added
    ///
    void addAnimal(LivingElement*element);

    ///
    /// \brief logPopulation used to save info about population
    ///
    /// Function uses Logger class to save information about each animal
    /// into file for examination puproses
    void logPopulation();

    ///
    /// \brief setNewPopulation swaps new population with current one
    ///
    /// Used to set new population of animals on the map. It's used mostly
    /// when new generation of animals is created by Mutator class
//    void setNewPopulation(Population *);

    ///
    /// \brief getFoodElements gives acces to food elements
    /// \return vector of food elements
    ///
    /// Food elements are extruded from Food model. No changes can be made
    /// using this function to the model
    const std::vector<Element*>& getFoodElements();

    ////
    /// \brief updateFoodModel emits proper signals from food model to update view
    ///
    /// Should be called after changes in food elements is done
    void updateFoodModel();

    ///
    /// \brief getAnimalElemensts gives acces to animal elements
    /// \return vector of animal elements
    ///
    /// Animal elements are extruded from Population model
    const std::vector<LivingElement*>& getAnimalElemensts();

    ///
    /// \brief boundingRect used to access map size
    /// \return map size
    ///
    /// Map size is used for display purposes by GUI, and for simulation by
    /// PhysicsEngine
    QRect boundingRect();

    void confirmValueChanges();
    void confirmStructoreChanges();

signals:
    void valuesChanged();
private:

    int _xSize;
    int _ySize;


    std::vector<Element*> _foodElements;
    std::vector<LivingElement*> _populationElements;

    QQmlApplicationEngine* engine;
};

#endif // MAP_H
