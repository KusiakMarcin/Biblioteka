#ifndef RENTALS_H
#define RENTALS_H
#include <iostream>
#include "Books.h"
#include <QDate>

enum columns{ID,CLIENTID,BOOKID,BORROWDAY,RETURNDAY};

struct Rentals{
    int ID;
    int clientID;
    int bookID;
    QDate borrowedDay;
    QDate returnDay;

};

#endif // RENTALS_H
