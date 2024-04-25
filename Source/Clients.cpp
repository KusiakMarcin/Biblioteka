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

//Clients::PopulateTable(){





//}
