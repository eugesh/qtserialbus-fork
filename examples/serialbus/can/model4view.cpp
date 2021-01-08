#include "model4view.h"


Model4view::Model4view(QObject *parent) : QAbstractTableModel (parent)
{

}

Model4view::~Model4view()
{

}

bool Model4view::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    Q_UNUSED(count)

    beginInsertRows(parent, row, row);

    endInsertRows();

    return true;
}

bool Model4view::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    Q_UNUSED(count)

    beginRemoveRows(parent, row, row);

    endRemoveRows();

    return true;
}

QVariant Model4view::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role == Qt::DisplayRole) && (orientation == Qt::Horizontal))
    {
        switch (section) {
        case 0:
            return "Timestamp";
        case 1:
            return "Flags";
        case 2:
            return "CAN-ID   DLC  Data";
        }
    }

    return QVariant();
}

QVariant Model4view::data(const QModelIndex &index, int role) const
{
    if (! (role == Qt::DisplayRole || role == Qt::EditRole))
        return QVariant();

    int row = index.row();
    int column = index.column();

    switch (column) {
    case 0:
        return m_framesQ[row][0];
    case 1:
        return m_framesQ[row][1];
    case 2:
        return m_framesQ[row][2];
    }

    return QVariant();
}

int Model4view::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_framesQ.size();
}

int Model4view::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 3;
}

void Model4view::insertFrame(const QStringList & list)
{
    insertRow(m_framesQ.size());

    m_framesQ.enqueue(list);

    if (m_qLimit < rowCount()) {
        removeFirstRow();
    }
}

void Model4view::removeFirstRow()
{
    if (rowCount()) {
        removeRow(0);

        m_framesQ.dequeue();
    }
}

void Model4view::deletAll()
{
    while (rowCount()) {
        removeFirstRow();
    }
}
