#ifndef BOOKS_H
#define BOOKS_H
#include <iostream>

class Books{

private:
    int BookID;
    std::string Tytul;
    int AutorID;
    int IloscEgzemplarzy;
    int RokWydania;
    int GatunekID;
    int LiczbaWypozyczen;

public:
    Books(int id, std::string, int autor_id,int ilosc_egzemplarzy,int rok_wydania,int gatunek_id,int liczba_wypozyczen);
    //DeleteField();
    //DeleteElement
    //CreateElement
    //CreateField();
    ~Books();


};

#endif BOOKS_H //
