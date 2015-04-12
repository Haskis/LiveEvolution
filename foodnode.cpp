#include "foodnode.h"

#include <QSGVertexColorMaterial>

#include "shader.h"

FoodNode::FoodNode(PlantElement* element):
    m_pElement(element)
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

void FoodNode::updateGeometry(){

    //Draw animal body
    updateCircleTable(m_pElement->radius(),m_pElement->xPosition(),m_pElement->yPosition());

    markDirty(QSGNode::DirtyGeometry);
}
