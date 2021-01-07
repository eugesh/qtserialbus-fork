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

    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    void insertFrame(const QStringList & list);
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    void removeFirstRow();
    void deletAll();
    void setQLimit(int limit) { m_qLimit = limit; }
    int getQLimit() { return m_qLimit; }

private:
    QQueue<QStringList> m_framesQ;
    int m_qLimit = 5;
};

#endif // MODEL4VIEW_H
