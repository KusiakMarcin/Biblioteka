#include "Headers/Books.h"
#include "Headers/sqlite3.h"
#include <iostream>


using namespace std;

Books::Books(int id, std::string tytul, int autor_id,int ilosc_egzemplarzy,int rok_wydania,int gatunek_id,int liczba_wypozyczen){

    int BookID = id;
    Tytul = tytul;
    AutorID = autor_id;
    IloscEgzemplarzy = ilosc_egzemplarzy;
    RokWydania = rok_wydania;
    GatunekID = gatunek_id;
    LiczbaWypozyczen = liczba_wypozyczen;

}





