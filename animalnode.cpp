
#include "animalnode.h"

#include <QSGVertexColorMaterial>

#include "shader.h"

AnimalNode::SensorsNode::SensorsNode()
{
    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), 0);

    geometry->setDrawingMode(GL_LINES);

    geometry->setLineWidth(1);
    setGeometry(geometry);
    setFlag(QSGNode::OwnsGeometry);

    QSGVertexColorMaterial *material = new QSGVertexColorMaterial;
    setMaterial(material);
    setFlag(QSGNode::OwnsMaterial);
}

void AnimalNode::SensorsNode::updateGeometry(LivingElement* element)
{
    QSGGeometry *g = geometry();
    g->allocate(element->m_sensors.size()*2);
    QSGGeometry::ColoredPoint2D *v = g->vertexDataAsColoredPoint2D();

    int counter = 0;

    //Transparency
    int alphaValue = 25;

    for(const LivingElement::Sensor& sensor: element->getSensors()){
        v[counter++].set(element->xPosition()+element->radius()*sin(sensor._position+element->rotation()),
                         element->yPosition()+ element->radius()*cos(sensor._position+element->rotation()),
                         sensor._color.red(),sensor._color.green(),sensor._color.blue(),alphaValue);

        v[counter++].set(element->xPosition()+sensor._range*sin(sensor._position+element->rotation()),
                         element->yPosition()+sensor._range*cos(sensor._position+element->rotation()),
                         sensor._color.red(),sensor._color.green(),sensor._color.blue(),alphaValue);
    }
}


AnimalNode::MotorsNode::MotorsNode()
{
    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), 0);

    geometry->setDrawingMode(GL_TRIANGLES);

    geometry->setLineWidth(1);
    setGeometry(geometry);
    setFlag(QSGNode::OwnsGeometry);

    QSGVertexColorMaterial *material = new QSGVertexColorMaterial;
    setMaterial(material);
    setFlag(QSGNode::OwnsMaterial);
}

void AnimalNode::MotorsNode::updateGeometry(LivingElement* element)
{
    QSGGeometry *g = geometry();
    g->allocate(element->m_motors.size()*6);
    QSGGeometry::ColoredPoint2D *v = g->vertexDataAsColoredPoint2D();

    // Motor width in angles
    float mW = 0.4;


    //Transparency
    int alphaValue = 70;

    int counter = 0;
    //Draw motor ( experimental values)
    for(const LivingElement::Motor& motor: element->getMotors()){

        //Motor color depends on actual motor power
        QColor color = QColor(Qt::black);
        color.setAlpha(alphaValue);
        if(motor._power>=0){
            color.setBlue(motor._power*255);
            color.setRed(0);
        }
        else{
            color.setBlue(0);
            color.setRed(-motor._power*255);
        }

        v[counter++].set(element->xPosition()+element->radius()*sin(motor._position+element->rotation()+mW),
                         element->yPosition()+element->radius()*cos(motor._position+element->rotation()+mW),
                         color.red(),color.green(),color.blue(),color.alpha());

        v[counter++].set(element->xPosition()+element->radius()*sin(motor._position+element->rotation()-mW),
                         element->yPosition()+element->radius()*cos(motor._position+element->rotation()-mW),
                         color.red(),color.green(),color.blue(),color.alpha());

        v[counter++].set(element->xPosition()+2*element->radius()*sin(motor._position+element->rotation()+mW),
                         element->yPosition()+2*element->radius()*cos(motor._position+element->rotation()+mW),
                         color.red(),color.green(),color.blue(),color.alpha());

        v[counter++].set(element->xPosition()+element->radius()*sin(motor._position+element->rotation()-mW),
                         element->yPosition()+element->radius()*cos(motor._position+element->rotation()-mW),
                         color.red(),color.green(),color.blue(),color.alpha());

        v[counter++].set(element->xPosition()+2*element->radius()*sin(motor._position+element->rotation()+mW),
                         element->yPosition()+2*element->radius()*cos(motor._position+element->rotation()+mW),
                         color.red(),color.green(),color.blue(),color.alpha());

        v[counter++].set(element->xPosition()+2*element->radius()*sin(motor._position+element->rotation()-mW),
                         element->yPosition()+2*element->radius()*cos(motor._position+element->rotation()-mW),
                         color.red(),color.green(),color.blue(),color.alpha());
    }
}



//************************************************************************************************
AnimalNode::AnimalNode(LivingElement* element):
    m_lElement(element)
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

void AnimalNode::updateGeometry()
{
    //Check color
    QSGSimpleMaterial<State> *m;
    m = static_cast<QSGSimpleMaterial<State>* > (material());
    if(m_lElement->selected())
        m->state()->color = QColor(Qt::blue);
    else{
        m->state()->color = m_lElement->color();
    }
    //Draw animal body
    updateCircleTable(m_lElement->radius(),m_lElement->xPosition(),m_lElement->yPosition());

    // TO DO (change so there won't be unnecesary deletion and creation)
    removeAllChildNodes();
    SensorsNode* sn = new SensorsNode;
    sn->updateGeometry(m_lElement);
    appendChildNode(sn);

    MotorsNode* mn = new MotorsNode;
    mn->updateGeometry(m_lElement);
    appendChildNode(mn);

    markDirty(QSGNode::DirtyGeometry);
}
