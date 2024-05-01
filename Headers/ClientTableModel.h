#ifndef CLIENTTABLEMODEL_H
#define CLIENTTABLEMODEL_H
#include <QAbstractTableModel>
#include "sqlite3.h"
#include "Clients.h"



class ClientTableModel : public QAbstractTableModel{

    Q_OBJECT
    enum Collumns{ClientID,Imie,Nazwisko,Email,Adres,NumerKarty};

public:

    ClientTableModel(QObject *parent = nullptr);
    //int populatetable(const QModelIndex &parent = QModelIndex());
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

};



#endif // CLIENTTABLEMODEL_H
