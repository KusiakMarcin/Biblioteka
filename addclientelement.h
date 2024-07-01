#ifndef ADDCLIENTELEMENT_H
#define ADDCLIENTELEMENT_H
#include "Headers/database.h"
#include <QDialog>
namespace Ui {class addclientelement;}

class addclientelement : public QDialog
{
    Q_OBJECT

public:
    explicit addclientelement(database *Db,QWidget *parent = nullptr);
    ~addclientelement();

private slots:
    void on_pushButton_dodajKlienta_2_clicked();

    //void on_pushButton_dodajKlienta_2_clicked();

private:
    Ui::addclientelement *ui;
    database *Db;
};

#endif // ADDCLIENTELEMENT_H
