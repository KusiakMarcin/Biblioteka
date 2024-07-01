#include "Headers/ClientTableModel.h"
#include "Headers/Clients.h"
#include <QDebug>
#include "Headers/sqlite3.h"

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
        QVector<QString>tmp;
        tmp.append(QString(sqlite3_column_int(stmt,0)));
        tmp.append((char*)sqlite3_column_text(stmt,1));
        tmp.append((char*)sqlite3_column_text(stmt,2));
        tmp.append((char*)sqlite3_column_text(stmt,3));
        tmp.append(QString(sqlite3_column_int(stmt,4)));
        tmp.append((char*)sqlite3_column_text(stmt,5));
        tmp.append(QString(sqlite3_column_int(stmt,6)));


        datalist.append(tmp);
    }
    qDebug()<<".count():"<<datalist.count();


}
void ClientTableModel::addElement(){


    insertRow(rowCount());
}


void ClientTableModel::deleteElement(){


}
