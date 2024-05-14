#ifndef CLIENTS_H
#define CLIENTS_H
#include <iostream>
using namespace std;
class Clients{

private:
    int ClientID;
    string Imie;
    string Nazwisko;
    string Email;
    string Adres;
    int NumerKarty;

public:
    Clients(int id,string email,string imie,string nazwisko,string adres,int numerkarty);
    //Void PopulateTable();
    //
    //
    //
    ~Clients();

};

#endif // CLIENTS_H
