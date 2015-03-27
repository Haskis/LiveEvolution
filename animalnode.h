#ifndef ANIMALNODE_H
#define ANIMALNODE_H

#include <QSGGeometryNode>
#include <livingelement.h>
#include <QSGVertexColorMaterial>
class AnimalNode : public QSGGeometryNode
{

    class SensorsNode: public QSGGeometryNode{
        friend class AnimalNode;
        SensorsNode();
        void updateGeometry(LivingElement* element);
    };
    class MotorNode: public QSGGeometryNode{
        explicit MotorNode();
        void updateGeometry(LivingElement* element);
    };

public:
    explicit AnimalNode(LivingElement *element);

    void updateGeometry();
signals:

public slots:

private:
    void updateCircleTable();

    LivingElement* _lElement;
    std::vector<QSGGeometry::ColoredPoint2D> circleTable;
    std::vector<float> unitCircleTableX;
    std::vector<float> unitCircleTableY;
    void initCircleTable();
};

#endif // ANIMALNODE_H
