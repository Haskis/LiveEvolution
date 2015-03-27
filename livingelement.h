#ifndef LIVINGELEMENT_H
#define LIVINGELEMENT_H

#include "element.h"
#include "annbrain.h"
#include <vector>
#include <map>
#include "animalnode.h"
class LivingElement : public Element
{
    friend class Population;
    friend class AnimalNode;
//    friend class AnimalNode::MotorNode;




public:

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
    ~LivingElement();


    float xVelocity() const;
    float yVelocity() const;
    float aVelocity() const;

    void setXVelocity(float velocity);
    void setYVelocity(float velocity);
    void setAVelocity(float velocity);

    float mass() const;

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

    ///
    /// \brief structoreGene returns genetic information about structure of this element
    /// \return gene is described in a form of floats array
    ///
    /// This function enables classes which are resposible for mutation to extract
    /// genetic information about structure of this object. Genetic infromation is divided into two
    /// parts: structure (sensors, motors position and number) and behaviour ( brain )
    virtual std::vector<float> structureGene() const;

    ///
    /// \brief behaviourGene returns genetic information about behaviour of this element
    /// \return gene is described in a form of floats array
    ///
    /// This function enables classes which are resposible for mutation to extract
    /// genetic information about behaviour of this object. Genetic infromation is divided into two
    /// parts: structure (sensors, motors position and number) and behaviour ( brain )
    virtual std::vector<float> behaviourGene() const;


    virtual void updateStructure(const std::vector<float>& gene);
    virtual void updateBehaviour(const std::vector<float>* gene);

    const std::vector<Sensor> getSensors() const;
    const std::vector<Motor> getMotors() const;

private:

    float _xVelocity;  ///< Holds information about current velocity on map (xAxis), (look _yVelocity)
    float _yVelocity;  ///< Holds information about current velocity on map (yAxis), (look _xVelocity)
    float _aVelocity;  ///< Holds information about current angular velocity
    float _mass;       ///< Hodls information about animal mass

    bool _alive;
    unsigned int livingTime;

    ///
    /// \brief _sensors sensors container
    ///
    /// Each sensor works like an animal eye. it can sense color of element in it's range of view.
    /// Sensors are attached to LivingElement in some angular position <0:360). Each sensor has it's
    /// own maximum range
    ///

    std::vector<Sensor> _sensors;

    ///
    /// \brief _motors motors container
    ///
    /// Motors enables LivingElement to move across map. Each motor power can be adjusted. Motors have
    /// predefined maximum force ( rotation, and forward moving ). Motors are attached to Living Element
    /// in some angular position <0; 360)
    std::vector<Motor> _motors;

    ///
    /// \brief _energy current energy level
    ///
    /// LivingElement lives till his energy level is above 0 or till he is killed. Moving around map
    /// consumes energy, also time passing by consumes energy. Energy can be restored by eating other elements.
    float _energy;

    ///
    /// \brief _brain describes LivingElement behaviour
    ///
    /// Brain is used to translate sensors inputs into motors outputs. It's mostly unique for each LivingElement
    Brain* _brain;

    bool checkIntersection(QVector2D circleCentre, float circleRadius, QVector2D segmentBegin, QVector2D segmentEnd);
};

#endif // LIVINGELEMENT_H
