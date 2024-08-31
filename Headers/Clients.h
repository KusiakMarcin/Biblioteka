#ifndef CLIENTS_H
#define CLIENTS_H
#include <iostream>
#include <QString>

//enum clientColumn{ID,NAME,LASTNAME,ADRESS,PHONE_NUM,EMAIL,CARD_NUM};

struct Clients{
        int ClientID;
        QString Imie;
        QString Nazwisko;
        QString Adres;
        int NumerTelefonu;
        QString Email;
        int NumerKarty;
};

//using namespace std;
//class Clients{

//private:
//    int ClientID;
//    QString Imie;
//    QString Nazwisko;
//    QString Adres;
//    int NumerTelefonu;
//    QString Email;
//    int NumerKarty;

//public:
//    Clients(int id,QString imie,QString nazwisko,QString adres,int telefon,QString email,int numerkarty);
//    void setDataList(database *Db);
//    ~Clients();

//};

#endif // CLIENTS_H
