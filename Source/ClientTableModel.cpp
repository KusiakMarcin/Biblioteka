#include "Headers/ClientTableModel.h"
#include "Headers/Clients.h"
#include <QDebug>


ClientTableModel::ClientTableModel(database *Db, QObject *parent)
    : QAbstractTableModel(parent)
{
    this->setDataList(Db);
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
void ClientTableModel::setDataList(database *Db){

    const char* sql = "SELECT * FROM Klienci;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(Db->Db,sql,-1,&stmt,NULL);
    if (rc != SQLITE_OK) {
        qDebug()<< sqlite3_errmsg(Db->Db);
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
        Clients tmp;

        tmp.ClientID = sqlite3_column_int(stmt,0);
        tmp.Imie =(char*)sqlite3_column_text(stmt,1);
        tmp.Nazwisko =(char*)sqlite3_column_text(stmt,2);
        tmp.Adres =(char*)sqlite3_column_text(stmt,3);
        tmp.NumerTelefonu = sqlite3_column_int(stmt,4);
        tmp.Email=(char*)sqlite3_column_text(stmt,5);
        tmp.NumerKarty =sqlite3_column_int(stmt,6);
        datalist.append(tmp);
    }
    qDebug()<<".count():"<<datalist.count();

}

void ClientTableModel::addElement(QString imie,QString nazwisko,QString adres,int nrtel,QString email,database *Db){


    beginInsertRows(QModelIndex(),1,1);
    const char* sql = "SELECT * FROM Klienci WHERE nr_telefonu = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(Db->Db,sql,-1,&stmt,NULL);
    if (rc != SQLITE_OK) {
        qDebug()<< sqlite3_errmsg(Db->Db);
    }

    qDebug()<<"clicked";

    endInsertRows();
}


void ClientTableModel::deleteElement(){


}
