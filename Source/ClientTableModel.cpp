#include "Headers/ClientTableModel.h"
#include "Headers/Clients.h"
#include "Headers/database.h"
#include <QDebug>


ClientTableModel::ClientTableModel(database *Db, QObject *parent)
    : QAbstractTableModel(parent)
{
    datalist = Db->setDataList();
}

int ClientTableModel::rowCount(const QModelIndex &parent)const{

    return datalist.size();
}

int ClientTableModel::columnCount(const QModelIndex &parent)const{
    return 7;
}

QVariant ClientTableModel::data(const QModelIndex &index, int role)const{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    if (role == Qt::DisplayRole){
        switch(index.column()){
        case 0: return datalist.at(index.row()).ClientID;
        case 1: return datalist.at(index.row()).Imie;
        case 2: return datalist.at(index.row()).Nazwisko;
        case 3: return datalist.at(index.row()).Adres;
        case 4: return datalist.at(index.row()).NumerTelefonu;
        case 5: return datalist.at(index.row()).Email;
        case 6: return datalist.at(index.row()).NumerKarty;
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
            return QString("Adres");
        case 4:
            return QString("Numer telefonu");
        case 5:
            return QString("Email");
        case 6:
            return QString("Numer Karty");
        }
    }
    return QVariant();
}

void ClientTableModel::deleteElement(int row) {
    if (row < 0 || row >= datalist.size())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    Clients clientToDelete = datalist.at(row);
    if (Db->removeClient(clientToDelete.ClientID)) {
        datalist.removeAt(row);
    } else {
        qDebug() << "Failed to remove client with ID:" << clientToDelete.ClientID;
    }

    endRemoveRows();
}

//void ClientTableModel::addElement(Clients input){

//bool insertRows(int row, int count, const QModelIndex &parent){

//    return true;
//}
