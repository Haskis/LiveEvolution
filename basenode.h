#ifndef BASENODE_H
#define BASENODE_H

#include <QSGGeometryNode>
#include <QSGVertexColorMaterial>
class BaseNode: public QSGGeometryNode
{
public:

    virtual void updateGeometry() = 0;

protected:
    void updateCircleTable(float radius, float x, float y);


    void initCircleTable();

private:
    std::vector<QSGGeometry::ColoredPoint2D> circleTable;
    std::vector<float> unitCircleTableX;
    std::vector<float> unitCircleTableY;
};

#endif // ANIMALNODE_H
