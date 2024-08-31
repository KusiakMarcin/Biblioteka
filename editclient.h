#ifndef EDITCLIENT_H
#define EDITCLIENT_H

#include "Headers/database.h"
#include <QDialog>
#include "Headers/Clients.h"

namespace Ui {
class editclient;
}

class editclient : public QDialog
{
    Q_OBJECT

public:
    explicit editclient(database *Db,QWidget *parent = nullptr);
    void parseID(int id);
    ~editclient();

signals:
    void dataEdited();

public slots:


private:
    Ui::editclient *ui;
    database *Db;
    int ID;

};

#endif // EDITCLIENT_H
