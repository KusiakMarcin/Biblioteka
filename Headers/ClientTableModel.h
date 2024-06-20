#ifndef CLIENTTABLEMODEL_H
#define CLIENTTABLEMODEL_H
#include <QAbstractTableModel>
#include "sqlite3.h"
#include "Clients.h"



class ClientTableModel : public QAbstractTableModel{

    Q_OBJECT
private:
    QVector<QVector<QString>> datalist;
public:

    ClientTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void setData();
public slots:
    QVariant headerData(int section, Qt::Orientation orientation,int role)const override;
    void addElement();
    void deleteElement();
};



#endif // CLIENTTABLEMODEL_H
