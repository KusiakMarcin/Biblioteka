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

public slots:
    //bool ifBookExists(bool ifExists);
    bool ifClientExists(bool ifExists);


private:
    Ui::editrental *ui;
    database *Db;
    Rentals data;
    bool clientExists = true;
    bool bookExists = true;
};

#endif // EDITRENTAL_H
