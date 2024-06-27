#ifndef ADDCLIENTELEMENT_H
#define ADDCLIENTELEMENT_H
#include "Headers/database.h"
#include <QDialog>
namespace Ui {class addclientelement;}

class addclientelement : public QDialog
{
    Q_OBJECT

public:
    explicit addclientelement(QWidget *parent = nullptr);
    ~addclientelement();

private slots:
    void on_pushButton_dodajKlienta_2_clicked(database *Db);

private:
    Ui::addclientelement *ui;
};

#endif // ADDCLIENTELEMENT_H
