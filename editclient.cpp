#include "editclient.h"
#include "qdebug.h"
#include "ui_editclient.h"
#include <QPushButton>

editclient::editclient(database *Db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editclient)
{
    this->Db = Db;
    ui->setupUi(this);

    connect(ui->addButton,&QPushButton::clicked,this,&editclient::editElement);

}
void editclient::editElement(){
    if(ui->nameEdit->text()!=data.Imie){
        data.Imie=ui->nameEdit->text();
        Db->editElement(data.ClientID,0,1,ui->nameEdit->text());
    }
    if(ui->lastnameEdit->text()!=data.Nazwisko){
        data.Nazwisko=ui->lastnameEdit->text();
        Db->editElement(data.ClientID,0,2,ui->lastnameEdit->text());
    }
    if(ui->adressEdit->text()!=data.Adres){
        data.Adres = ui->adressEdit->text();
        Db->editElement(data.ClientID,0,3,ui->adressEdit->text());
    }
    if(ui->phoneEdit->text().toInt()!=data.NumerTelefonu){
        data.NumerTelefonu = ui->phoneEdit->text().toInt();
        Db->editElement(data.ClientID,0,4,ui->phoneEdit->text().toInt());
    }
    if(ui->emailEdit->text()!=data.Email){
        data.Email = ui->emailEdit->text();
        Db->editElement(data.ClientID,0,5,ui->emailEdit->text());
    }
    emit dataEdited();

}
void editclient::parseClient(Clients client){
    data = client;
    ui->nameEdit->setText(data.Imie);
    ui->lastnameEdit->setText(data.Nazwisko);
    ui->adressEdit->setText(data.Adres);
    ui->phoneEdit->setText(QString().setNum(data.NumerTelefonu));
    ui->emailEdit->setText(data.Email);
}

//fprintf(stdout, "Opened database successfully\n");
//Client.Imie = ui->lineEdit_imie_2->text();
//Client.Nazwisko = ui->lineEdit_nazwisko_2->text();
//Client.Adres = ui->lineEdit_adres_2->text();
//Client.NumerTelefonu = ui->lineEdit_nrtel_2->text().toInt();
//Client.Email = ui->lineEdit_email_2->text();

//if (Db->addNewClient(Client.Imie, Client.Nazwisko, Client.Adres, Client.NumerTelefonu, Client.Email)) {
//    emit submitedClient();
//    QMessageBox::information(this, "Information", "Record inserted successfully.");

//} else {
//    QMessageBox::critical(this, "Error", "Failed to insert record into database.");
//}


//}

editclient::~editclient()
{
    delete ui;
}
