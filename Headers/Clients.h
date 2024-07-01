#ifndef CLIENTS_H
#define CLIENTS_H
#include <iostream>
#include <QString>
using namespace std;
class Clients{

private:
    int ClientID;
    QString Imie;
    QString Nazwisko;
    QString Email;
    QString Adres;
    int NumerKarty;

public:
    Clients(int id,QString email,QString imie,QString nazwisko,QString adres,int numerkarty);
    //Void PopulateTable();
    //
    //
    //
    ~Clients();

};

#endif // CLIENTS_H
