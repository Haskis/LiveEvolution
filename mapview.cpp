#include "mapview.h"

SelectedElementData::SelectedElementData(QObject* parent):
    QObject(parent)
{
    m_energy = 0;
}

float SelectedElementData::energy(){
    return m_energy;
}

float SelectedElementData::motorOnePower(){
    return m_motorOnePower;
}

float SelectedElementData::motorTwoPower(){
    return m_motorTwoPower;
}

void SelectedElementData::update(LivingElement* element){
    m_energy = element->energy();
    m_motorOnePower = element->getMotors()[0]._power;
    m_motorTwoPower = element->getMotors()[1]._power;
    emit energyChanged(m_energy);
    emit motorOnePowerChanged(m_motorOnePower);
    emit motorTwoPowerChanged(m_motorTwoPower);
}


MapView::MapView(QQuickItem *parent) :
    QQuickItem(parent),
    m_selectedElement(new SelectedElementData(this)),
    m_map(nullptr)
{
    setFlags(QQuickItem::ItemHasContents);
    setAcceptedMouseButtons(Qt::AllButtons);
}


SelectedElementData*MapView::selectedElement() const{
    return m_selectedElement;
}

QSGNode*MapView::updatePaintNode(QSGNode* oldNode, QQuickItem::UpdatePaintNodeData*){

    if(!m_map)
        return oldNode;

    QSGNode* n = oldNode;
    if (!n) {
        n = new QSGNode;
    }
    if(m_structureChanged){
        n->removeAllChildNodes();
        for(size_t i=0; i<m_map->getFoodElements().size(); i++){
            n->appendChildNode(new FoodNode(m_map->getFoodElements()[i]));
        }
        for(size_t i=0;i<m_map->getAnimalElemensts().size(); i++){
            n->appendChildNode(new AnimalNode(m_map->getAnimalElemensts()[i]));
        }

        m_structureChanged = false;
    }
    if(m_valuesChanged){
        for(int i=0; i<n->childCount();i++){
            static_cast<BaseNode*>(n->childAtIndex(i))->updateGeometry();
        }
        m_valuesChanged = false;
    }

    return n;
}

void MapView::mousePressEvent(QMouseEvent* event){

    if(!m_map)
        return;


    for(LivingElement* elem : m_map->getAnimalElemensts()){
        QVector2D vec = QVector2D(elem->xPosition()-event->x(),elem->yPosition()-event->y());
        if(vec.length()<elem->radius()){
            elem->setSelected(true);
            m_selectedElement->update(elem);
            m_map->confirmValueChanges();
            break;
        }
        else{
            elem->setSelected(false);
            m_map->confirmValueChanges();
        }
    }

}

Map* MapView::map(){
    return m_map;
}

void MapView::setMap(Map* map){
    m_map = map;
    qDebug()<<"set map";
    connect(map,SIGNAL(valuesChanged()),this,SLOT(valuesChanged()));
    connect(map,SIGNAL(structureChanged()),this,SLOT(structureChanged()));
}

void MapView::valuesChanged(){
    m_valuesChanged = true;
    update();
}

void MapView::structureChanged(){
    m_structureChanged = true;
    update();
}
