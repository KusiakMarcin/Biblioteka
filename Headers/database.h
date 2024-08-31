#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"
#include <QString>
#include <QVector>
#include "Headers/Clients.h"
#include "Headers/Books.h"



class database{
private:
    sqlite3 *Db;


public:

    database();
    ~database();
    bool initDatabase();
    bool addNewClient(const QString& imie, const QString& nazwisko, const QString& adres, int nrtel, const QString& email);
    bool removeClient(int ClientID);
    bool editClient(const int id,const QString& imie, const QString& nazwisko, const QString& adres, int nrtel, const QString& email);
    QVector<Clients> setDataClient();
    bool removeBook(int BookID);
    QVector<Books> setDataBook();
   // QVector<Books> setDataBooks();


};

//const char *databaseMain = "databases/data.db";
//sqlite3 *Db;

#endif // DATABASE_H
