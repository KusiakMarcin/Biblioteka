#include "editrental.h"
#include "ui_editrental.h"
#include <QMessageBox>

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

    int flagDate=0;
    if(ui->borrowDate->date()>=ui->returnDate->date()){ flagDate=1; QMessageBox::information(this ,"Error","Incorrect input, borrowed dated cant be later than return date");}
    if(ui->clientID->text().toInt()!=data.clientID){
        emit parseClientID(ui->clientID->text().toInt());
        if(clientExists){
        data.clientID = ui->clientID->text().toInt();
            Db->editElement(data.ID,2,1,data.clientID);}
        else{QMessageBox::information(this ,"Error","Incorrect input, no such client");}
    }
    if(ui->bookID->text().toInt()!=data.bookID){
        emit parseBookID(ui->bookID->text().toInt());
        emit stockCheck(ui->bookID->text().toInt());
        if(bookExists&&!stockEmpty){
        data.bookID = ui->bookID->text().toInt();
        Db->editElement(data.ID,2,2,data.bookID);
        }
        else{
            if(!bookExists)QMessageBox::information(this ,"Error","Incorrect input, no such book");
            if(stockEmpty)QMessageBox::information(this ,"Error","Incorrect input, Stock is empty");
        }
    }
    if(ui->borrowDate->date()!=data.borrowedDay&&flagDate!=1){
        data.borrowedDay = ui->borrowDate->date();
        Db->editElement(data.ID,2,4,data.borrowedDay.toString("yyyy-MM-dd").toUtf8().constData());
    }
    if(ui->returnDate->date()!=data.returnDay&&flagDate!=1){
        data.returnDay = ui->returnDate->date();
        Db->editElement(data.ID,2,3,data.returnDay.toString("yyyy-MM-dd").toUtf8().constData());
    }

    emit dataEdited();

}
bool editrental::ifClientExists(bool ifExists){
    clientExists = ifExists;
}

bool editrental::ifBookExists(bool ifExists){
    bookExists = ifExists;
}
bool editrental::stockChecked(bool isEmpty){
    stockEmpty = isEmpty;
}

editrental::~editrental()
{
    delete ui;
}

