#ifndef ANIMALNODE_H
#define ANIMALNODE_H

#include "basenode.h"
#include "livingelement.h"

///
/// \brief The AnimalNode class for graphics representation of animal
///
/// This class uses Qt GeometryNode class to provide graphical
/// representation of animal with its sensors and motors
/// Sensors lightup on activation, motors are colored with intensity
/// depending on actual power
///
class AnimalNode : public BaseNode
{
    class SensorsNode: public QSGGeometryNode{
        friend class AnimalNode;
        explicit SensorsNode();
        void updateGeometry(LivingElement* element);
    };
    class MotorsNode: public QSGGeometryNode{
        friend class AnimalNode;
        explicit MotorsNode();
        void updateGeometry(LivingElement* element);
    };

public:
    explicit AnimalNode(LivingElement *element);

    virtual void updateGeometry();
private:

    // Life time not managed by AnimalNode
    LivingElement* m_lElement;
};

#endif // ANIMALNODE_H
