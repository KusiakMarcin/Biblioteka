#include "Headers/comboBox.h"


comboBox::comboBox(int dataMask,database *Db,QObject *parent){

    db=Db;
    switch (dataMask) {
    case 1:
       // db->setDataAuthor();
        break;
    case 2:
       // db->setDataGenre();
        break;
    default:
        break;
    }

}


int comboBox::rowCount(const QModelIndex& parent) const{


    return datalist.count();
}

QVariant comboBox::data(const QModelIndex& index, int role) const{

    if (!index.isValid() || index.row() >= datalist.size())
        return QVariant();

    if (role == Qt::DisplayRole) {
        return datalist.at(index.row());
    }

    return QVariant();
}
