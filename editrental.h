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
    void parseClientID(int ID);
    void parseBookID(int ID);
    void stockCheck(int ID);

public slots:
    bool ifBookExists(bool ifExists);
    bool ifClientExists(bool ifExists);
    bool stockChecked(bool isEmpty);

private:
    Ui::editrental *ui;
    database *Db;
    Rentals data;
    bool clientExists = true;
    bool bookExists = true;
    bool stockEmpty = false;
};

#endif // EDITRENTAL_H
