#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"
#include <QString>
#include <QVector>
#include "Headers/Clients.h"

struct type {
    int integer;
    QString string;
};

class database{
private:
    sqlite3 *Db;


public:

    database();
    ~database();
    bool initDatabase();
    bool addNewClient(const QString& imie, const QString& nazwisko, const QString& adres, int nrtel, const QString& email);
    bool removeClient(int ClientID);
    QVector<Clients> setDataList();
    type clientDataHandler(int column,int ID);

};

//const char *databaseMain = "databases/data.db";
//sqlite3 *Db;

#endif // DATABASE_H
