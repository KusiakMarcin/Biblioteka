#include "Headers/ClientTableModel.h"
#include "Headers/Clients.h"

ClientTableModel::ClientTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

int ClientTableModel::rowCount(const QModelIndex &parent)const{

    return 0;
}

int ClientTableModel::columnCount(const QModelIndex &parent)const{
    return 6;
}

QVariant ClientTableModel::data(const QModelIndex &index, int role)const{

    if (role == Qt::DisplayRole)
        return QString("Row%1, Column%2").arg(index.row() + 1).arg(index.column() +1);

    return QVariant();
}
QVariant ClientTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("ID");
        case 1:
            return QString("Imie");
        case 2:
            return QString("Nazwisko");
        case 3:
            return QString("Email");
        case 4:
            return QString("Adres");
        case 5:
            return QString("Numer Karty");
        }
    }
    return QVariant();
}

void ClientTableModel::addElement(){


}
void ClientTableModel::deleteElement(){


}
