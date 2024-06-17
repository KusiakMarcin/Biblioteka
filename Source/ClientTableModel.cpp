#include "Headers/ClientTableModel.h"
#include "Headers/Clients.h"

ClientTableModel::ClientTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

int ClientTableModel::rowCount(const QModelIndex &parent)const{

    return 1;

}

int ClientTableModel::columnCount(const QModelIndex &parent)const{
    return 6;
}

QVariant ClientTableModel::data(const QModelIndex &index, int role)const{

    if (role == Qt::DisplayRole){
        switch(index.column()){
        case 0: return QString("q");
        case 1: return QString("w");
        case 2: return QString("e");
        case 3: return QString("r");
        case 4: return QString("t");
        case 5: return QString("y");

        }
    }

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


    insertRow(rowCount());
}


void ClientTableModel::deleteElement(){


}
