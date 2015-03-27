#ifndef POPULATION_H
#define POPULATION_H

#include <QAbstractListModel>
#include <QDebug>
#include <QColor>
class LivingElement;

class Population : public QAbstractListModel
{
    Q_OBJECT
    friend class Map;
public:
    Population();

    enum AnimalRoles {
        XPositionRole = Qt::UserRole + 1,
        YPositionRole,
        RadiusRole,
        ColorRole,
        RotationRole
    };

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    void append(LivingElement*element);
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

public slots:
    // Functions used from QML View to access sensor data ( can't be done by AnimalRoles if we want to keep "dynamic" way)
    int sensorCount(int elemIndex);
    QColor sensorColor(int elemIndex, int sensorIndex) const;
    float sensorPosition(int elemIndex, int sensorIndex) const;
    float sensorRange(int elemIndex, int sensorIndex) const;

    int motorCount(int elemIndex);
    float motorPosition(int elemIndex, int sensorIndex) const;
    float motorAForce(int elemIndex, int sensorIndex) const;
    float motorRForce(int elemIndex, int sensorIndex) const;
    float motorPower(int elemIndex, int sensorIndex) const;
protected:
     QHash<int, QByteArray> roleNames() const;

private:
    std::vector<LivingElement*> _populationElements;
};

#endif // POPULATION_H
