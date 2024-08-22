#ifndef CLIENTTABLEMODEL_H
#define CLIENTTABLEMODEL_H
#include <QAbstractTableModel>
#include <QItemSelectionModel>
#include "sqlite3.h"
#include "Headers/database.h"
#include <QLineEdit>
#include "Clients.h"




class ClientTableModel : public QAbstractTableModel{

    Q_OBJECT
    QVector<Clients> datalist;
public:

    ClientTableModel(database *Db, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,int role)const override;
//    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
public slots:
    //void addElement(Clients input);

//    void deleteElement();
signals:
    void dataUpdated();
};



#endif // CLIENTTABLEMODEL_H
