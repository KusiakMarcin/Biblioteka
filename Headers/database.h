#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"
#include <QString>
#include <QVector>
#include "Headers/Clients.h"
#include "Headers/Books.h"
#include "Headers/Rentals.h"



class database{
private:
    sqlite3 *Db;


public:

    database();
    ~database();
    bool initDatabase();
    bool addNewClient(const QString& imie, const QString& nazwisko, const QString& adres, int nrtel, const QString& email);
    bool addNewBook(const QString& tytul, int rokWydania , int liczbaEgzemplarzy, int autor, int gatunek);
    bool addRental(int clientID,int bookID,QDate borrowDate, QDate returnDate);

    bool editClient(const int id,const QString& imie, const QString& nazwisko, const QString& adres, int nrtel, const QString& email);
    QVector<Clients> setDataClient();
    bool removeBook(int BookID);
    bool removeClient(int ClientID);
    bool removeRental(int rentalID);
    QVector<Books> setDataBook();
    QVector<Rentals> setRentalList();
    QVector<QString> setDataAuthor();
    QVector<QString> setDataGenre();
   // QVector<Books> setDataBooks();


};

//const char *databaseMain = "databases/data.db";
//sqlite3 *Db;

#endif // DATABASE_H
