#include"Headers/Clients.h"
#include "Headers/sqlite3.h"
#include <iostream>


Clients:: Clients(int id,string email,string imie,string nazwisko,string adres,int numerkarty){

    ClientID = id;
    Email = email;
    Imie = imie;
    Nazwisko = nazwisko;
    Adres = adres;
    NumerKarty = numerkarty;

}
QVector<QString>* Clients::convertQStringList(){
    QVector<QString> *item = new QVector<QString>;
    item->append({
        QString(ClientID),
        QString::fromStdString(Imie),
        QString::fromStdString(Nazwisko),
        QString::fromStdString(Email),
        QString::fromStdString(Adres),
        QString(NumerKarty)
    });

    return item;

}
//Clients::PopulateTable(){





//}
