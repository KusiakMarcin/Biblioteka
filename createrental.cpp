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
    ui->borrowDate->setDate(QDate().currentDate());
    ui->returnDate->setDate(QDate().currentDate().addMonths(3));

}

bool CreateRental::addRental(){
    Rentals tmp;
    tmp.clientID = ui->client->text().toInt();
    tmp.bookID = ui->book->text().toInt();
    tmp.returnDay = ui->returnDate->date();
    tmp.borrowedDay = ui->borrowDate->date();
    emit parseClientID(tmp.clientID);
    emit parseBookID(tmp.bookID);
    emit stockCheck(tmp.bookID);
    if(!clientExists){
        QMessageBox::information(this,"Error","Incorrect data input, no such client");
        return false;
    }
    if(!bookExists){
        QMessageBox::information(this,"Error","Incorrect data input, no such book");
        return false;
    }
    if(stockEmpty){
        QMessageBox::information(this,"Error","Incorrect data input, stock is empty");

        return false;
    }
    if(tmp.borrowedDay>tmp.returnDay){QMessageBox::information(this,"Error","Incorrect data input, return date can't be set before borrow date");return false;}
    if(tmp.clientID==0){QMessageBox::information(this,"Error","Incorrect data input, Client ID"); return false;}
    db->addRental(tmp.clientID,tmp.bookID,tmp.borrowedDay,tmp.returnDay);
    emit dataSubmited();
    ui->borrowDate->setDate(QDate().currentDate());
    ui->returnDate->setDate(QDate().currentDate().addMonths(3));
    return true;
}
void CreateRental::ifClientExists(bool ifExists){
    clientExists = ifExists;
}

void CreateRental::ifBookExists(bool ifExists){
    bookExists = ifExists;
}
void CreateRental::stockChecked(bool isEmpty){
    stockEmpty = isEmpty;
}
CreateRental::~CreateRental()
{

    delete ui;
}
