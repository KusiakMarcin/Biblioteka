#include <Headers/RentalsTableModel.h>


RentalsTableModel::RentalsTableModel(database* Db,QObject *parent) : QAbstractTableModel(parent)
{
    db = Db;
    datalist = db->setRentalList();

}
int RentalsTableModel::rowCount(const QModelIndex &parent)const {
    return datalist.size();
}
int RentalsTableModel::columnCount(const QModelIndex &parent) const{

    return 6;
}
QVariant RentalsTableModel::data(const QModelIndex &index, int role) const {
    float pen = 0;
    if(!index.isValid()|| role != Qt::DisplayRole) return QVariant();
    if(role ==Qt::DisplayRole){
    switch (index.column()) {
    case 0:
        return datalist.at(index.row()).ID;
        break;
    case 1:
        return datalist.at(index.row()).clientID;
            break;
    case 2:
            return datalist.at(index.row()).bookID;
            break;
    case 3:
            return datalist.at(index.row()).borrowedDay.toString("yyyy-MM-dd");
            break;
    case 4:
            return datalist.at(index.row()).returnDay.toString("yyyy-MM-dd");
            break;
    case 5:
            pen = datalist.at(index.row()).returnDay.daysTo(QDate().currentDate())*0.20;
            if(pen<=0.0)return 0;
            else return pen;
            break;
    default:
        break;
    }
    }
    return QVariant();
}

Rentals RentalsTableModel::findRental(int ID){
    for(int i=0;i<datalist.size();i++){
    if(datalist[i].ID!=ID)continue;
    else return datalist[i];
    }
    return Rentals();
}
QVariant RentalsTableModel::headerData(int section, Qt::Orientation orientation,int role)const{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("ID");
        case 1:
            return QString("ID Klienta");
        case 2:
            return QString("ID Książki");
        case 3:
            return QString("Data Wypożyczenia");
        case 4:
            return QString("Data Zwrotu");
        case 5:
            return QString("Kary");

        }
    }
    return QVariant();
}

void RentalsTableModel::resetModel(){
    beginResetModel();
    datalist.clear();
    datalist = db->setRentalList();
    endResetModel();
}

void RentalsTableModel::addElement(){

}
void RentalsTableModel::deleteElement(){

}

bool RentalsTableModel::hasRentals(int ID){
    for(int i=0;i<datalist.size();i++){
        if(datalist[i].clientID!=ID)continue;
        else return true;
    }
    return false;
}

bool RentalsTableModel::isRented(int ID){
    for(int i=0;i<datalist.size();i++){
        if(datalist[i].bookID!=ID)continue;
        else return true;
    }
    return false;
}
