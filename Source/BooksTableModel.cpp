#include "Headers/BooksTableModel.h"
#include "Headers/Books.h"
#include <QDebug>

BooksTableModel::BooksTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

int BooksTableModel::rowCount(const QModelIndex &parent)const{

    return datalist.size();
}

int BooksTableModel::columnCount(const QModelIndex &parent)const{
    return 7;
}

QVariant BooksTableModel::data(const QModelIndex &index, int role)const{

    if (role == Qt::DisplayRole){
        return datalist.at(index.row()).at(index.column());
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
void BooksTableModel::setDataList(database *Db){
/*
    const char* sql = "SELECT * FROM Ksiazki;";
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

*/
}
void BooksTableModel::addElement(){


    insertRow(rowCount());
}


void BooksTableModel::deleteElement(){}
