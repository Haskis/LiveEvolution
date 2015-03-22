#ifndef ELEMENT_H
#define ELEMENT_H

#include <QColor>
#include "map.h"

class MeatEater;
class PlantEater;
class PlantElement;


///
/// \brief The Element class is a base class for all elements on board
///
/// Elements divide into LivingElements(MeatEater, PlantEater) and PlanElement
/// Each element can be placed in some space on map and can interact with other
/// elements using handleIntersection functions
///
///
class Element
{
public:
    Element();

    float xPosition() const;
    float yPosition() const;
    void setXPosition(float xPosition);
    void setYPosition(float yPosition);
    void setRandomPosition(const QRect& rect);

protected:

    ///
    /// \brief handleIntersection
    /// \param e
    ///
    /// This function should call e->handleIntersection(*this), in this way proper handleIntersection function call will
    /// be invoked. handleIntersection functions describe how object should react when it colides with other element.
    ///
    virtual void handleIntersection(Element *e) = 0;
    virtual void handleIntersection(MeatEater *e) = 0;
    virtual void handleIntersection(PlantEater *e) = 0;
    virtual void handleIntersection(PlantElement *e) = 0;

private:

    float _xPosition;  ///< Holds information about current position on map (xAxis), (look _yPosition)
    float _yPosition;  ///< Holds information about current position on map (yAxis), (look _xPosition)

    QColor _color;     ///< Holds information about current element color

    ///
    /// \brief collidingElements list of colliding elements
    ///
    /// This table is updated each time checkoutEnviroment function is called, it holds pointers to Elements colliding
    /// with this element. This list is used for faster access to colliding elements in Phycisc Engine class. Only
    /// elements not traversable are collected
    std::vector<Element*> collidingElements;
};

#endif // ELEMENT_H
