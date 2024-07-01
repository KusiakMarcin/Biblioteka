#include <Headers/RentalsTableModel.h>


RentalsTableModel::RentalsTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}
int RentalsTableModel::rowCount(const QModelIndex &parent)const {
    return datalist.size();
}
int RentalsTableModel::columnCount(const QModelIndex &parent) const{

    return 4;
}
QVariant RentalsTableModel::data(const QModelIndex &index, int role) const {


}
QVariant RentalsTableModel::headerData(int section, Qt::Orientation orientation,int role)const{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("ID Klienta");
        case 1:
            return QString("ID Książki");
        case 2:
            return QString("Data Wypożyczenia");
        case 3:
            return QString("Data Zwrotu");

        }
    }
    return QVariant();
}


void RentalsTableModel::setDataList(database *Db){

}
void RentalsTableModel::addElement(){

}
void RentalsTableModel::deleteElement(){

}
