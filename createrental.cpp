#include "createrental.h"
#include "ui_createrental.h"
#include <QDebug>
#include <QMessageBox>
#include "Headers/Rentals.h"


CreateRental::CreateRental(database *Db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateRental)
{
    ui->setupUi(this);
    db =Db;
    connect(ui->pushButton,&QPushButton::clicked,this,&CreateRental::addRental);
}

bool CreateRental::addRental(){
    Rentals tmp;
    tmp.clientID = ui->client->text().toInt();
    tmp.bookID = ui->book->text().toInt();
    tmp.returnDay = ui->returnDate->date();
    tmp.borrowedDay = ui->borrowDate->date();
    if(tmp.borrowedDay>tmp.returnDay){QMessageBox::information(this,"Error","Incorrect data input, return date can't be set before borrow date");return false;}
    if(tmp.clientID==0){QMessageBox::information(this,"Error","Incorrect data input, Client ID"); return false;}
    db->addRental(tmp.clientID,tmp.bookID,tmp.borrowedDay,tmp.returnDay);
    emit dataSubmited();
    return true;
}

CreateRental::~CreateRental()
{
    delete ui;
}
