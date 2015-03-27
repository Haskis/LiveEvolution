#include "animalnode.h"
#include <QSGVertexColorMaterial>



AnimalNode::SensorsNode::SensorsNode()
{
    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), 0);

    geometry->setDrawingMode(GL_LINES);

    geometry->setLineWidth(2);
    setGeometry(geometry);
    setFlag(QSGNode::OwnsGeometry);

    QSGVertexColorMaterial *material = new QSGVertexColorMaterial;
    setMaterial(material);
    setFlag(QSGNode::OwnsMaterial);

}

void AnimalNode::SensorsNode::updateGeometry(LivingElement* element)
{
    QSGGeometry *g = geometry();
    g->allocate(element->_sensors.size()*2);
    QSGGeometry::ColoredPoint2D *v = g->vertexDataAsColoredPoint2D();

    int counter =0;
    for(const LivingElement::Sensor& sensor: element->getSensors()){
        v[counter++].set(element->xPosition(),element->yPosition(),
                         sensor._color.red(),sensor._color.green(),sensor._color.blue(),sensor._color.alpha());
        v[counter++].set(element->xPosition()+sensor._range*sin(sensor._position+element->rotation()),element->yPosition()+sensor._range*cos(sensor._position+element->rotation()),
                         sensor._color.red(),sensor._color.green(),sensor._color.blue(),sensor._color.alpha());
    }
}


AnimalNode::MotorNode::MotorNode()
{

}

void AnimalNode::MotorNode::updateGeometry(LivingElement* element)
{

}



//************************************************************************************************
AnimalNode::AnimalNode(LivingElement* element):
    _lElement(element)
{
    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), 0);

    geometry->setDrawingMode(GL_TRIANGLE_STRIP);

    geometry->setLineWidth(1);
    setGeometry(geometry);
    setFlag(QSGNode::OwnsGeometry);

    QSGVertexColorMaterial *material = new QSGVertexColorMaterial;
    setMaterial(material);
    setFlag(QSGNode::OwnsMaterial);

    initCircleTable();
    updateGeometry();
}

void AnimalNode::updateGeometry()
{
    //Draw animal body
    updateCircleTable();

    SensorsNode* sn = new SensorsNode;
    removeAllChildNodes();
    sn->updateGeometry(_lElement);
    appendChildNode(sn);

    markDirty(QSGNode::DirtyGeometry);
}

void AnimalNode::updateCircleTable()
{
    QSGGeometry *g = geometry();
    g->allocate(unitCircleTableX.size());
    QSGGeometry::ColoredPoint2D *v = g->vertexDataAsColoredPoint2D();

    for(int i=0; i<unitCircleTableX.size(); i++){
        v[i].set(unitCircleTableX[i]*_lElement->radius()+_lElement->xPosition(), unitCircleTableY[i]*_lElement->radius()+_lElement->yPosition(),
                 _lElement->color().red(),_lElement->color().green(),_lElement->color().blue(),_lElement->color().alpha());
    }
}

void AnimalNode::initCircleTable()
{
    const unsigned HALF_PREC = 10;
    const float angInc = M_PI / static_cast<float>(HALF_PREC);
    const float cosInc = cos(angInc);
    const float sinInc = sin(angInc);
    //unsigned coordIdx = 0;


    float xc = 1.0f;
    float yc = 0.0f;

    unitCircleTableX.clear();
    unitCircleTableY.clear();

    unitCircleTableX.push_back(xc);
    unitCircleTableY.push_back(yc);

    for (int iAng= 1; iAng<HALF_PREC ; ++iAng)  {
        float xcNew = cosInc * xc - sinInc * yc;
        yc = sinInc * xc + cosInc * yc;
        xc = xcNew;
        unitCircleTableX.push_back(xc);
        unitCircleTableY.push_back(yc);

        unitCircleTableX.push_back(xc);
        unitCircleTableY.push_back(-yc);
    }

    unitCircleTableX.push_back(0.0f);
    unitCircleTableY.push_back(1.0f);
}

