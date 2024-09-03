#ifndef RENTALSTABLEMODEL_H
#define RENTALSTABLEMODEL_H
#include <QAbstractTableModel>
#include "sqlite3.h"
#include "Headers/database.h"
#include <QDebug>


class RentalsTableModel : public QAbstractTableModel{

    Q_OBJECT
    QVector<Rentals> datalist;
    database *db;

public:

    RentalsTableModel(database *Db,QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,int role)const override;
    void resetModel();
    Rentals findRental(int ID);
    bool hasRentals(int ID);
    bool isRented(int ID);
public slots:


    void addElement();
    void deleteElement();
};



#endif // CLIENTTABLEMODEL_H
