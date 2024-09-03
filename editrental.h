#ifndef EDITRENTAL_H
#define EDITRENTAL_H

#include <QDialog>
#include "Headers/database.h"
#include "Headers/Rentals.h"

namespace Ui {
class editrental;
}

class editrental : public QDialog
{
    Q_OBJECT

public:
    explicit editrental(database *Db, QWidget *parent = nullptr);
    void parseRental(Rentals rental);
    void editElement();
    ~editrental();

signals:
    void dataEdited();

private:
    Ui::editrental *ui;
    database *Db;
    Rentals data;
};

#endif // EDITRENTAL_H
