#ifndef ANIMALNODE_H
#define ANIMALNODE_H

#include <basenode.h>
#include <livingelement.h>
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

    LivingElement* _lElement;
    std::vector<QSGGeometry::ColoredPoint2D> circleTable;
    std::vector<float> unitCircleTableX;
    std::vector<float> unitCircleTableY;
};

#endif // ANIMALNODE_H
