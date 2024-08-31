#ifndef BOOKSTABLEMODEL_H
#define BOOKSTABLEMODEL_H
#include <QAbstractTableModel>
#include "Books.h"
#include <QAbstractTableModel>
#include "Headers/database.h"



class BooksTableModel : public QAbstractTableModel{

    Q_OBJECT
    QVector<Books> datalist;
    database * Db;

public:

    BooksTableModel(database *Db,QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,int role)const override;
    void resetModel();
public slots:


};



#endif // CLIENTTABLEMODEL_H
