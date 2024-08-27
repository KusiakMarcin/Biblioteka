#include "addbookelement.h"
#include "ui_addbookelement.h"

addbookelement::addbookelement(database* Db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addbookelement)
{
    ui->setupUi(this);
}

addbookelement::~addbookelement()
{
    delete ui;
}
