#ifndef ADDBOOKELEMENT_H
#define ADDBOOKELEMENT_H

#include <QDialog>
#include "Headers/database.h"

namespace Ui {
class addbookelement;
}

class addbookelement : public QDialog
{
    Q_OBJECT

public:
    explicit addbookelement(database*Db, QWidget *parent = nullptr);
    ~addbookelement();

private:
    Ui::addbookelement *ui;
    database *Db;
};

#endif // ADDBOOKELEMENT_H
