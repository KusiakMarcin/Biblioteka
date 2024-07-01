#include "Headers/BooksTableModel.h"
#include "Headers/Books.h"

BooksTableModel::BooksTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

int BooksTableModel::rowCount(const QModelIndex &parent)const{

    return 1;
}

int BooksTableModel::columnCount(const QModelIndex &parent)const{
    return 7;
}

QVariant BooksTableModel::data(const QModelIndex &index, int role)const{

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
QVariant BooksTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("ID");
        case 1:
            return QString("Tytuł");
        case 2:
            return QString("Autor");
        case 3:
            return QString("Rok Wydania");
        case 4:
            return QString("Gatunek");
        case 5:
            return QString("Liczba Egzemplarzy");
        case 6:
            return QString("Liczba Wypożyczonych");
        }
    }
    return QVariant();
}

void BooksTableModel::addElement(){


    insertRow(rowCount());
}


void BooksTableModel::deleteElement(){}
