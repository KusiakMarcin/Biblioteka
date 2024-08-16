#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"
#include <QString>
#include <QVector>


class database{
private:
    sqlite3 *Db;
    union trolling {
        int integer;
        QString string;
    };

public:

    database();
    ~database();
    bool initDatabase();
    bool addNewClient(const QString& imie, const QString& nazwisko, const QString& adres, int nrtel, const QString& email);
    trolling clientDataHandler(int column,int ID);

};

//const char *databaseMain = "databases/data.db";
//sqlite3 *Db;

#endif // DATABASE_H
