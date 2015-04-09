#include "mapview.h"


SelectedElementData::SelectedElementData(QObject* parent):
    QObject(parent)
{
    _energy = 0;
}

float SelectedElementData::energy(){
    return _energy;
}

float SelectedElementData::motorOnePower()
{
    return _motorOnePower;
}

float SelectedElementData::motorTwoPower()
{
    return _motorTwoPower;
}

void SelectedElementData::update(LivingElement* element)
{
    _energy = element->energy();
    _motorOnePower = element->getMotors()[0]._power;
    _motorTwoPower = element->getMotors()[1]._power;
    emit energyChanged(_energy);
    emit motorOnePowerChanged(_motorOnePower);
    emit motorTwoPowerChanged(_motorTwoPower);
}


MapView::MapView(QQuickItem *parent) :
    QQuickItem(parent),
    _map(nullptr),
    _selectedElement(new SelectedElementData(this))
{
    setFlags(QQuickItem::ItemHasContents);
    setAcceptedMouseButtons(Qt::AllButtons);
}


SelectedElementData*MapView::selectedElement() const{
    return _selectedElement;
}

QSGNode*MapView::updatePaintNode(QSGNode* oldNode, QQuickItem::UpdatePaintNodeData*)
{
    if(!_map)
        return oldNode;

    QSGNode* n = oldNode;
    if (!n) {
        n = new QSGNode;
    }
    if(_structureChanged){
        n->removeAllChildNodes();
        for(int i=0; i<_map->getFoodElements().size(); i++){
            n->appendChildNode(new FoodNode(_map->getFoodElements()[i]));
        }
        for(int i=0;i<_map->getAnimalElemensts().size(); i++){
            n->appendChildNode(new AnimalNode(_map->getAnimalElemensts()[i]));
        }

        _structureChanged = false;
    }
    if(_valuesChanged){
        for(int i=0; i<n->childCount();i++){
            static_cast<BaseNode*>(n->childAtIndex(i))->updateGeometry();
        }
        _valuesChanged = false;
    }

    return n;
}

void MapView::mousePressEvent(QMouseEvent* event)
{
    if(!_map)
        return;


    for(LivingElement* elem : _map->getAnimalElemensts()){
        QVector2D vec = QVector2D(elem->xPosition()-event->x(),elem->yPosition()-event->y());
        if(vec.length()<elem->radius()){
            elem->setSelected(true);
            _selectedElement->update(elem);
            _map->confirmValueChanges();
            break;
        }
        else{
            elem->setSelected(false);
            _map->confirmValueChanges();
        }
    }

}

Map* MapView::map(){

}

void MapView::setMap(Map* map){
    _map = map;
    qDebug()<<"set map";
    connect(map,SIGNAL(valuesChanged()),this,SLOT(valuesChanged()));
    connect(map,SIGNAL(structureChanged()),this,SLOT(structureChanged()));
}

void MapView::valuesChanged(){
    _valuesChanged = true;
    update();
}

void MapView::structureChanged(){
    _structureChanged = true;
    update();
}



