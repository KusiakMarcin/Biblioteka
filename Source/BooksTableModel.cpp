#include "Headers/BooksTableModel.h"
#include "Headers/Books.h"
#include <QDebug>

BooksTableModel::BooksTableModel(database *Db, QObject *parent)
    : QAbstractTableModel(parent)
{
    datalist = Db->setDataBook();
    this->Db=Db;
    qDebug()<<"listsize"<<datalist.size();
}

int BooksTableModel::rowCount(const QModelIndex &parent)const{
    if(parent.isValid()) return 0;
    return datalist.size();
}

int BooksTableModel::columnCount(const QModelIndex &parent)const{
    if(parent.isValid())return 0;
    return 7;
}

QVariant BooksTableModel::data(const QModelIndex &index, int role)const{

    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    if (role == Qt::DisplayRole){
        switch(index.column()){
        case 0: return datalist.at(index.row()).BookID;
        case 1: return datalist.at(index.row()).Title;
        case 2: return datalist.at(index.row()).Author;
        case 3: return datalist.at(index.row()).RokWydania;
        case 4: return datalist.at(index.row()).Genre;
        case 5: return datalist.at(index.row()).Stock;
        case 6: return datalist.at(index.row()).NumberRented;
        }
    }
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
void BooksTableModel::resetModel() {
    beginResetModel();
    datalist.clear();
    datalist = Db->setDataBook();
    endResetModel();

}


