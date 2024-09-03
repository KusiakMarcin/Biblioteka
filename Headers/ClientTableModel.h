#ifndef CLIENTTABLEMODEL_H
#define CLIENTTABLEMODEL_H
#include <QAbstractItemModel>
#include <QAbstractTableModel>
#include <QItemSelectionModel>
#include <QVariant>
#include "sqlite3.h"
#include "Headers/database.h"
#include <QLineEdit>
#include "Clients.h"





class ClientTableModel : public QAbstractTableModel{

    Q_OBJECT
    QVector<Clients> datalist;
    database * Data;

    Clients newClient;
public:

    ClientTableModel(database *Db, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,int role)const override;
    void resetModel();


public slots:
    Clients findClient(int ID/*int left,int right*/);

//    void deleteElement();
signals:
    void dataUpdated();
};



#endif // CLIENTTABLEMODEL_H
