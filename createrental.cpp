#include "createrental.h"
#include "ui_createrental.h"

CreateRental::CreateRental(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateRental)
{
    ui->setupUi(this);
    db =Db;
}

CreateRental::~CreateRental()
{
    delete ui;
}
