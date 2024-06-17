#ifndef BOOKSTABLEMODEL_H
#define BOOKSTABLEMODEL_H
#include <QAbstractTableModel>
#include "sqlite3.h"
#include "Books.h"



class BooksTableModel : public QAbstractTableModel{

    Q_OBJECT

public:

    BooksTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
public slots:
    QVariant headerData(int section, Qt::Orientation orientation,int role)const override;
    void addElement();
    void deleteElement();
};



#endif // CLIENTTABLEMODEL_H
