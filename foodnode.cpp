#include "foodnode.h"
#include <QSGVertexColorMaterial>
#include "shader.h"


FoodNode::FoodNode(PlantElement* element):
    _pElement(element)
{
    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 0);

    geometry->setDrawingMode(GL_TRIANGLE_STRIP);

    geometry->setLineWidth(1);
    setGeometry(geometry);
    setFlag(QSGNode::OwnsGeometry);

    QSGSimpleMaterial<State> *material = Shader::createMaterial();
    material->state()->color = element->color();
    setMaterial(material);

    setFlag(QSGNode::OwnsMaterial);

    initCircleTable();
    updateGeometry();
}

void FoodNode::updateGeometry()
{

    //Draw animal body
    updateCircleTable(_pElement->radius(),_pElement->xPosition(),_pElement->yPosition());

    markDirty(QSGNode::DirtyGeometry);
}
