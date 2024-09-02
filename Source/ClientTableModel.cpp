#include "Headers/ClientTableModel.h"
#include "Headers/Clients.h"
#include <QDebug>


ClientTableModel::ClientTableModel(database *Db, QObject *parent)               //Model danych dla tabeli Klientów. Jako argument przyjmuję wskaźnik do obiektu database, który
    : QAbstractTableModel(parent)                                               //komunikuje się z bazą danych.Drugi argument parent jest wskaźnikiem do rodzica.
{
    datalist = Db->setDataClient();
    Data = Db;

}

int ClientTableModel::rowCount(const QModelIndex &parent)const{                 //Zwraca liczbe danych w modelu tabeli
    if(parent.isValid()) return 0;
    return datalist.size();
}

int ClientTableModel::columnCount(const QModelIndex &parent)const{              //Zwraca liczbe kolumn w modelu tabeli
    if(parent.isValid())return 0;
    return 7;
}

QVariant ClientTableModel::data(const QModelIndex &index, int role)const{       //
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

Clients* ClientTableModel::findClient(int ID/*int left,int right*/){
//    if(left<0||right>datalist.size())return nullptr;
//    if(right==left)return nullptr;
//    int pivot=left+(right-left)/2;
//    if(pivot==left)pivot++;
//    if(datalist[pivot].ClientID<ID)return findClient(ID,left,pivot);
//    if(datalist[pivot].ClientID>ID)return findClient(ID,pivot,right);
//    if(datalist[pivot].ClientID == ID)return &datalist[pivot];
    for(int i=0;i<datalist.size();i++){
        if(datalist[i].ClientID!=ID)continue;
        else return &datalist[i];
    }
    return NULL;

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
void ClientTableModel::resetModel() {
    beginResetModel();
    datalist.clear();
    datalist = Data->setDataClient();
    endResetModel();

}






