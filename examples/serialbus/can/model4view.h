#ifndef MODEL4VIEW_H
#define MODEL4VIEW_H

#include <QAbstractTableModel>
#include <QCanBusFrame>
#include <QQueue>

class Model4view : public QAbstractTableModel
{
public:
    explicit Model4view(QObject *parent = nullptr);
    ~Model4view() Q_DECL_OVERRIDE;

    //QModelIndex parent(const QModelIndex &child) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    // bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    void insertFrame(const QStringList & list);
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

private:
    // QQueue<QCanBusFrame> _framesQ;
    QQueue<QStringList> _framesQ;
};

#endif // MODEL4VIEW_H
