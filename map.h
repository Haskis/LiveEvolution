#ifndef MAP_H
#define MAP_H

#include <QRect>
#include <QObject>
#include <vector>

class QQmlApplicationEngine;

class PlantElement;
class LivingElement;
class Mutator;


class Map: public QObject
{
    Q_OBJECT

public:
    explicit Map(int xSize, int ySize);
    ~Map();

    ///
    /// \brief addFood adds food into Food internal container
    /// \param food food element to be added
    ///
    /// Adds food element into internal container. Food elements
    /// can be accessed using getFoodElements() function
    void addFood(PlantElement* food);

    ///
    /// \brief addAnimal adds animal into internal container
    /// \param element animal element to be added
    ///
    /// Adds animal element into internal container.
    void addAnimal(LivingElement*element);

    ///
    /// \brief getFoodElements gives acces to food elements
    /// \return vector of food elements
    ///
    /// Food elements are extruded from Food model. No changes can be made
    /// using this function to the model
    const std::vector<PlantElement*>& getFoodElements();

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

    ///
    /// \brief cleanDead check is anyone is dead, then clean
    ///
    /// This function removes dead animals from internal container, then it calls
    /// function to create new animal using mutator object
    ///
    void cleanDead(Mutator *mutator);

    void confirmValueChanges();
    void confirmStructureChanges();

signals:
    void valuesChanged();
    void structureChanged();
private:

    int m_xSize;
    int m_ySize;

    std::vector<PlantElement*> m_foodElements;
    std::vector<LivingElement*> m_populationElements;

};

#endif // MAP_H
