#ifndef LIVINGELEMENT_H
#define LIVINGELEMENT_H

#include <vector>

#include "element.h"
#include "annbrain.h"
#include "map.h"
#include "animalnode.h"
class LivingElement : public Element
{
    friend class Population;
    friend class AnimalNode;

public:

    enum Type{
        MEAT_EATER,
        PLANT_EATER,
    };

    struct Sensor{
        Sensor();

        QColor _color;
        float _position;
        float _range;
        float _angle;
    };
    struct Motor{
        Motor();

        float _position;
        float _aForce; // Angular force
        float _rForce; // Radious force
        float _power;
    };

    ///
    /// \brief LivingElement
    /// \param brain concrete brain used by this element, brain is managed and deleted by this object
    ///
    LivingElement(Brain *brain);
    virtual ~LivingElement();


    float xVelocity() const;
    float yVelocity() const;
    float aVelocity() const;

    virtual Type type() const = 0;

    void setXVelocity(float velocity);
    void setYVelocity(float velocity);
    void setAVelocity(float velocity);


    ///
    /// \brief checkoutEnviroment updates element according to enviroment
    /// \param map
    ///
    /// In inherited classes this function enables object to sense other elements on map, and depending on situation
    /// it can update object sensors state. While looking for elements near this element collision table is updated
    /// to speed up other functions (PhysicsEngine)
    ///
    virtual void checkoutEnviroment(Map& map);

    ///
    /// \brief reactToEnviroment Updates element output based on input
    ///
    /// In inherited classes this function should set element state (e.g. velocity) based on sensor data
    ///
    virtual void reactToEnviroment();

//    ///
//    /// \brief structoreGene returns genetic information about structure of this element
//    /// \return gene is described in a form of floats array
//    ///
//    /// This function enables classes which are resposible for mutation to extract
//    /// genetic information about structure of this object. Genetic infromation is divided into two
//    /// parts: structure (sensors, motors position and number) and behaviour ( brain )
//    virtual const std::vector<float>& structureGene() const;

    ///
    /// \brief behaviourGene returns genetic information about behaviour of this element
    /// \return gene is described in a form of floats array
    ///
    /// This function enables classes which are resposible for mutation to extract
    /// genetic information about behaviour of this object. Genetic infromation is divided into two
    /// parts: structure (sensors, motors position and number) and behaviour ( brain )
    virtual const std::vector<float>& behaviourGene() const;

    //virtual void updateStructure(const std::vector<float>& gene);
    virtual void updateBehaviour(const std::vector<float>& gene);

    const std::vector<Sensor>& getSensors() const;
    const std::vector<Motor>& getMotors() const;
private:

    float m_xVelocity;  ///< Holds information about current velocity on map (xAxis), (look _yVelocity)
    float m_yVelocity;  ///< Holds information about current velocity on map (yAxis), (look _xVelocity)
    float m_aVelocity;  ///< Holds information about current angular velocity

    unsigned int m_livingTime;

    ///
    /// \brief _sensors sensors container
    ///
    /// Each sensor works like an animal eye. it can sense color of element in it's range of view.
    /// Sensors are attached to LivingElement in some angular position <0:360). Each sensor has it's
    /// own maximum range
    ///

    std::vector<Sensor> m_sensors;

    ///
    /// \brief _motors motors container
    ///
    /// Motors enables LivingElement to move across map. Each motor power can be adjusted. Motors have
    /// predefined maximum force ( rotation, and forward moving ). Motors are attached to Living Element
    /// in some angular position <0; 360)
    std::vector<Motor> m_motors;

    ///
    /// \brief _brain describes LivingElement behaviour
    ///
    /// Brain is used to translate sensors inputs into motors outputs. It's mostly unique for each LivingElement
    Brain* m_brain;

    bool checkIntersection(QVector2D circleCentre, float circleRadius, QVector2D segmentBegin, QVector2D segmentEnd);
    void senseElement(Element *elem, float max);
};

#endif // LIVINGELEMENT_H
