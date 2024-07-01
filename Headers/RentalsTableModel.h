#ifndef RENTALSTABLEMODEL_H
#define RENTALSTABLEMODEL_H
#include <QAbstractTableModel>
#include "sqlite3.h"
#include "Headers/database.h"



class RentalsTableModel : public QAbstractTableModel{

    Q_OBJECT
    QVector<QVector<QString>> datalist;
public:

    RentalsTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,int role)const override;
public slots:

    void setDataList(database *Db);
    void addElement();
    void deleteElement();
};



#endif // CLIENTTABLEMODEL_H
