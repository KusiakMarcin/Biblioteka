#ifndef REMOVECLIENTELEMENT_H
#define REMOVECLIENTELEMENT_H
#include "Headers/database.h"
#include <QDialog>
#include "Headers/Clients.h"

namespace Ui {class removeclientelement;}

class removeclientelement : public QDialog
{
    Q_OBJECT

public:
    explicit removeclientelement(database *Db,QWidget *parent = nullptr);
    ~removeclientelement();
signals:
    void submitInput(Clients input);

private slots:
    void onRemoveClient();

private:
    Ui::removeclientelement *ui;
    Clients Client;
    database *Db;
};

#endif // REMOVECLIENTELEMENT_H
