#ifndef ADDBOOKELEMENT_H
#define ADDBOOKELEMENT_H

#include <QDialog>
#include "Headers/database.h"
#include "Headers/comboBox.h"

namespace Ui {
class addbookelement;
}

class addbookelement : public QDialog
{
    Q_OBJECT

public:
    explicit addbookelement(database*Db, QWidget *parent = nullptr);
    ~addbookelement();

public slots:
    void addElement();
signals:
    void dataSubmited();

private:
    Ui::addbookelement *ui;
    database *db;
    comboBox *authorModel;
    comboBox *genreModel;


};

#endif // ADDBOOKELEMENT_H
