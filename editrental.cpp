#include "editrental.h"
#include "ui_editrental.h"

editrental::editrental(database * Db ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editrental)
{
    this->Db = Db;
    ui->setupUi(this);

    connect(ui->pushButton,&QPushButton::clicked,this,&editrental::editElement);
}

void editrental::parseRental(Rentals rental){
    data = rental;
    ui->clientID->setText(QString().setNum(data.clientID));
    ui->bookID->setText(QString().setNum(data.bookID));
    ui->borrowDate->setDate(data.borrowedDay);
    ui->returnDate->setDate(data.returnDay);
}

void editrental::editElement(){
    if(ui->clientID->text().toInt()!=data.clientID){
        data.clientID = ui->clientID->text().toInt();
        Db->editElement(data.ID,2,1,data.clientID);
    }
    if(ui->bookID->text().toInt()!=data.bookID){
        data.bookID = ui->bookID->text().toInt();
        Db->editElement(data.ID,2,2,data.bookID);
    }
    if(ui->borrowDate->date()!=data.borrowedDay){
        data.borrowedDay = ui->borrowDate->date();
        Db->editElement(data.ID,2,4,data.borrowedDay.toString("yyyy-MM-dd").toUtf8().constData());
    }
    if(ui->returnDate->date()!=data.returnDay){
        data.returnDay = ui->returnDate->date();
        Db->editElement(data.ID,2,3,data.returnDay.toString("yyyy-MM-dd").toUtf8().constData());
    }

    emit dataEdited();
}
editrental::~editrental()
{
    delete ui;
}
