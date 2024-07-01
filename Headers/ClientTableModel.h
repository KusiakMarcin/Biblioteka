#ifndef CLIENTTABLEMODEL_H
#define CLIENTTABLEMODEL_H
#include <QAbstractTableModel>
#include <QItemSelectionModel>
#include "sqlite3.h"
#include "Clients.h"
#include "Headers/database.h"




class ClientTableModel : public QAbstractTableModel{

    Q_OBJECT
    QVector<QVector<QString>> datalist;
public:

    ClientTableModel(database *Db, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
public slots:
    QVariant headerData(int section, Qt::Orientation orientation,int role)const override;
    void setDataList(database *Db);
    void addElement();
    void deleteElement();
};



#endif // CLIENTTABLEMODEL_H
