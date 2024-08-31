#ifndef BOOKS_H
#define BOOKS_H
#include <iostream>
#include <QString>
//enum bookcolumn{}
struct Books{
    int BookID;
    QString Title;
    QString Author;
    int RokWydania;
    QString Genre;
    int NumberRented;
    int Stock;
};

#endif //BOOKS_H
