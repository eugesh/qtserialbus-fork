#include "model4view.h"


Model4view::Model4view(QObject *parent) : QAbstractTableModel (parent)
{

}

Model4view::~Model4view() {

}

bool Model4view::insertRows(int row, int count, const QModelIndex &parent) {
    Q_UNUSED(parent)

    beginInsertRows(parent, row, row);

    if(_framesQ.size() == row && count == 1) {
    }

    endInsertRows();

    return true;
}

QVariant Model4view::data(const QModelIndex &index, int role) const {
    if (! (role == Qt::DisplayRole || role == Qt::EditRole))
        return QVariant();

    int row = index.row();
    int column = index.column();

    switch (column) {
    case 0:
        return _framesQ[row][0];
    case 1:
        return _framesQ[row][1];
    case 2:
        return _framesQ[row][2];
    }
}

int Model4view::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)

    return _framesQ.size();
}

int Model4view::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)

    return 3;
}

void Model4view::insertFrame(const QStringList & list) {
    insertRow(_framesQ.size());

    _framesQ.enqueue(list);
}
