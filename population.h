#ifndef POPULATION_H
#define POPULATION_H

#include <QAbstractListModel>

class LivingElement;

class Population : public QAbstractListModel
{
public:
    Population();

    enum AnimalRoles {
        XPositionRole = Qt::UserRole + 1,
        YPositionRole,
        RadiusRole,
        ColorRole
    };

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    void addAnimal(LivingElement*element);
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
     QHash<int, QByteArray> roleNames() const;

private:
    std::vector<LivingElement*> populationElements;
};

#endif // POPULATION_H
