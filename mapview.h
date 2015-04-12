#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QQuickItem>

#include "map.h"
#include "animalnode.h"
#include "foodnode.h"

class SelectedElementData: public QObject{
    Q_OBJECT

public:
    Q_PROPERTY(float energy READ energy NOTIFY energyChanged)
    Q_PROPERTY(float motorOnePower READ motorOnePower NOTIFY motorOnePowerChanged)
    Q_PROPERTY(float motorTwoPower READ motorTwoPower NOTIFY motorTwoPowerChanged)

    explicit SelectedElementData(QObject *parent = NULL);

    float energy();
    float motorOnePower();
    float motorTwoPower();
    void update(LivingElement *element);

signals:
    void energyChanged(float energy);
    void motorOnePowerChanged(float power);
    void motorTwoPowerChanged(float power);
private:
    float m_energy;
    float m_motorOnePower;
    float m_motorTwoPower;
};

class MapView : public QQuickItem
{
    Q_OBJECT
public:

    Q_PROPERTY(Map* map READ map WRITE setMap)
    Q_PROPERTY(SelectedElementData* selectedElement READ selectedElement NOTIFY selectedElementChanged)

    explicit MapView(QQuickItem *parent = 0);
    SelectedElementData* selectedElement() const;

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

    void mousePressEvent(QMouseEvent *event);

    Map* map();
    void setMap(Map* map);

signals:
    void selectedElementChanged(SelectedElementData* elem);

private slots:
    void valuesChanged();
    void structureChanged();

private:
    SelectedElementData* m_selectedElement;
    Map* m_map;
    AnimalNode* m_aNode;
    bool m_valuesChanged = true;
    bool m_structureChanged = true;

};

#endif // MAPVIEW_H
