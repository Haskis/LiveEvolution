#include "mapview.h"

MapView::MapView(QQuickItem *parent) :
    QQuickItem(parent),
    _map(nullptr)
{
    setFlag(QQuickItem::ItemHasContents);
}

QSGNode*MapView::updatePaintNode(QSGNode* oldNode, QQuickItem::UpdatePaintNodeData*)
{
    if(!_map)
        return oldNode;
    //qDebug()<<"Update";

    QSGNode* n = oldNode;
    if (!n) {
        n = new QSGNode;//AnimalNode();

    }
    if(_structureChanged){
        n->removeAllChildNodes();
        for(int i=0;i<_map->getAnimalElemensts().size(); i++){
            n->appendChildNode(new AnimalNode(_map->getAnimalElemensts()[i]));
        }
        _structureChanged = false;
    }
    if(_valuesChanged){
        for(int i=0; i<n->childCount();i++){
            dynamic_cast<AnimalNode*>(n->childAtIndex(i))->updateGeometry();
        }
        _valuesChanged = false;
    }


    return n;

//    //Little trick (dont call updateGeometry twice);
//    if(_colorChanged){
//        n->updateColor(_color);
//        _colorChanged = false;
//    }
//    if(_lineWidthChanged){
//        n->updateLineWidth(_lineWidth);
//        _lineWidthChanged = false;
//    }

//    if (_geometryChanged) {
//        n->updateGeometry(boundingRect(),samples,samplesEkg, _samplesShown, _samplesOffset);
//        _geometryChanged = false;
//    }

//    return n;

}

//void MapView::geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry)
//{
////    _geometryChanged = true;

//    update();
//    //    QQuickItem::geometryChanged(newGeometry, oldGeometry);
//}

Map*MapView::map()
{

}

void MapView::setMap(Map* map)
{
    _map = map;
    qDebug()<<"set map";
    connect(map,SIGNAL(valuesChanged()),this,SLOT(test()));
}

void MapView::test()
{
    _valuesChanged = true;
    update();
    //qDebug()<<"Test";
}

