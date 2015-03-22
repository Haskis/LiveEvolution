#ifndef FOOD_H
#define FOOD_H

#include <QAbstractListModel>

class Element;

class Food : public QAbstractListModel
{
public:
    Food();

    enum FoodRoles {
        XPositionRole = Qt::UserRole + 1,
        YPositionRole,
        RadiusRole,
        ColorRole
    };

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
     QHash<int, QByteArray> roleNames() const;

private:
    std::vector<Element*> _foodElements;
};

#endif // FOOD_H
