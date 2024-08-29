#ifndef ADDCLIENTELEMENT_H
#define ADDCLIENTELEMENT_H
#include "Headers/database.h"
#include <QDialog>
#include "Headers/Clients.h"
#include "Headers/database.h"
namespace Ui {class addclientelement;}

class addclientelement : public QDialog
{
    Q_OBJECT

public:
    explicit addclientelement(database *Db,QWidget *parent = nullptr);
    ~addclientelement();
signals:
    void submitInput(Clients input);
    void submitedClient();

private slots:
    void on_pushButton_dodajKlienta_2_clicked();

    //void on_pushButton_dodajKlienta_2_clicked();

private:
    Ui::addclientelement *ui;
    Clients Client;
    database *Db;
};

#endif // ADDCLIENTELEMENT_H
