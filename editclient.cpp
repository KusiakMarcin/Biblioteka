#include "editclient.h"
#include "ui_editclient.h"
#include <QPushButton>

editclient::editclient(database *Db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editclient)
{
    this->Db = Db;
    ui->setupUi(this);

    //connect(ui->addButton,&QPushButton::clicked(),)

}

void editclient::parseID(int id){
    ID = id;
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
