#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QQuickItem>
#include <map.h>
#include <animalnode.h>
class MapView : public QQuickItem
{
    Q_OBJECT
public:

    Q_PROPERTY(Map* map READ map WRITE setMap)
    explicit MapView(QQuickItem *parent = 0);

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);
    //void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

    //void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);

    Map* map();
    void setMap(Map* map);

public slots:
private slots:
    void test();
private:
    Map* _map;
    AnimalNode* aNode;
    bool _valuesChanged = true;
    bool _structureChanged = true;

};

#endif // MAPVIEW_H
