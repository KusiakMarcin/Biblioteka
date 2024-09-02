#ifndef CREATERENTAL_H
#define CREATERENTAL_H
#include "Headers/database.h"
#include <QDialog>
#include "Headers/Rentals.h"
namespace Ui {
class CreateRental;
}

class CreateRental : public QDialog
{
    Q_OBJECT

public:
    explicit CreateRental(database *Db, QWidget *parent = nullptr);
    ~CreateRental();

signals:
    void submitedRental();

private:
    Ui::CreateRental *ui;
    database *Db;
    Clients Client;
    Books Book;
    Rentals Rental;
};

#endif // CREATERENTAL_H
