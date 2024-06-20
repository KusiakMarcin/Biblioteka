#include "Headers/ClientTableModel.h"
#include "Headers/Clients.h"
#include "Source/Clients.cpp"
#include <QDebug>

ClientTableModel::ClientTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

int ClientTableModel::rowCount(const QModelIndex &parent)const{

    return datalist.size();

}

int ClientTableModel::columnCount(const QModelIndex &parent)const{
    return 6;
}

QVariant ClientTableModel::data(const QModelIndex &index, int role)const{
    Clients Item(123,"dasd","dasd","dasd","dasd",1234);
    QVector<QString> *gg = Item.convertQStringList();
    qDebug()<< gg;
    if (role == Qt::DisplayRole) {
        return datalist.at(index.row()).at(index.column());
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

void ClientTableModel::setData(){

    QVector<QString> item;
    datalist.append(item);

}
void ClientTableModel::addElement(){


    insertRow(rowCount());
}


void ClientTableModel::deleteElement(){


}
