#include "Headers/ClientTableModel.h"
#include "Headers/Clients.h"

ClientTableModel::ClientTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int ClientTableModel::rowCount(const QModelIndex &parent)const{

    return 3;
}

int ClientTableModel::columnCount(const QModelIndex &parent)const{
    return 7;
}

QVariant ClientTableModel::data(const QModelIndex &index, int role)const{

    if (role == Qt::DisplayRole)
        return QString("Row%1, Column%2").arg(index.row() + 1).arg(index.column() +1);

    return QVariant();
}
void ClientTableModel::addElement(){

}
void ClientTableModel::deleteElement(){


}
