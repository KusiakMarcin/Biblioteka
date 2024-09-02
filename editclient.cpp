#include "editclient.h"
#include "ui_editclient.h"
#include <QPushButton>
#include <QMessageBox>

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

editclient::~editclient()
{
    delete ui;
}

void editclient::on_addButton_clicked()
{
    fprintf(stdout, "Opened database successfully\n");
    Client.Imie = ui->nameEdit->text();
    Client.Nazwisko = ui->lastnameEdit->text();
    Client.Adres = ui->adressEdit->text();
    Client.NumerTelefonu = ui->phoneEdit->text().toInt();
    Client.Email = ui->emailEdit->text();

    if (Db->editClient(ID, Client.Imie, Client.Nazwisko, Client.Adres, Client.NumerTelefonu, Client.Email)) {
        emit clientEdited();
        QMessageBox::information(this, "Information", "Record inserted successfully.");

    } else {
        QMessageBox::critical(this, "Error", "Failed to insert record into database.");
    }

}
