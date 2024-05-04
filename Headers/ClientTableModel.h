#ifndef CLIENTTABLEMODEL_H
#define CLIENTTABLEMODEL_H
#include <QAbstractTableModel>
#include "sqlite3.h"
#include "Clients.h"



class ClientTableModel : public QAbstractTableModel{

    Q_OBJECT

public:

    ClientTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
public slots:
    void addElement();
    void deleteElement();
};



#endif // CLIENTTABLEMODEL_H
