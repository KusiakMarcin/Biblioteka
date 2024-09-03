#ifndef CREATERENTAL_H
#define CREATERENTAL_H
#include "Headers/database.h"
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
    void dataEdited();
    void parseClientID(int ID);
    void parseBookID(int ID);
    void stockCheck(int ID);
    void dataSubmited();
public slots:
    bool addRental();
    void ifBookExists(bool ifExists);
    void ifClientExists(bool ifExists);
    void stockChecked(bool isEmpty);
private:
    Ui::CreateRental *ui;
    database *db;
    bool clientExists = true;
    bool bookExists = true;
    bool stockEmpty = false;
};

#endif // CREATERENTAL_H
