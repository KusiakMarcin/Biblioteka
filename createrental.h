#ifndef CREATERENTAL_H
#define CREATERENTAL_H
#include "Headers/database.h"
#include "Headers/Rentals.h"
#include <QDialog>

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
    void dataSubmited();
private:
    Ui::CreateRental *ui;
    database *db;
};

#endif // CREATERENTAL_H
