#include "createrental.h"
#include "ui_createrental.h"
#include <QDate>

CreateRental::CreateRental(database *Db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateRental)
{
    ui->setupUi(this);
    QDate currentDate = QDate::currentDate();
    ui->dateEdit->setDate(currentDate);
    ui->dateEdit_2->setDate(currentDate.addDays(90));
}

CreateRental::~CreateRental()
{
    delete ui;
}

