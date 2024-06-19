#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"
#include <QString>

class database{
public:
    sqlite3 *Db;
    database();
    ~database();
    bool initDatabase();
    bool addNewClient(const QString& imie, const QString& nazwisko, const QString& adres, int nrtel, const QString& email);

};

//const char *databaseMain = "databases/data.db";
//sqlite3 *Db;

#endif // DATABASE_H
