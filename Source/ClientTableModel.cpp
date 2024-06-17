#include "Headers/ClientTableModel.h"
#include "Headers/Clients.h"

ClientTableModel::ClientTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

int ClientTableModel::rowCount(const QModelIndex &parent)const{

<<<<<<< HEAD
    return 0;
=======
    return 1;
>>>>>>> ui_databasebranch
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
<<<<<<< HEAD
            return QString("Imie");
        case 2:
            return QString("Nazwisko");
        case 3:
            return QString("Email");
        case 4:
            return QString("Adres");
        case 5:
            return QString("Numer Karty");
=======
            return QString("Tytuł");
        case 2:
            return QString("Autor");
        case 3:
            return QString("Rok Wydania");
        case 4:
            return QString("Gatunek");
        case 5:
            return QString("Liczba Wypożyczeń");
        case 6:
            return QString("Liczba Egzemplarzy");
>>>>>>> ui_databasebranch
        }
    }
    return QVariant();
}

void ClientTableModel::addElement(){


    insertRow(rowCount());
}


void ClientTableModel::deleteElement(){


}
