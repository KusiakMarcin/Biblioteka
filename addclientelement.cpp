#include "addclientelement.h"

#include "ui_addclientelement.h"
#include <QMessageBox>

addclientelement::addclientelement(database *Db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addclientelement)
{
    this->Db=Db;
    ui->setupUi(this);


}

void addclientelement::on_pushButton_dodajKlienta_2_clicked(){
    fprintf(stdout, "Opened database successfully\n");
    Client.Imie = ui->lineEdit_imie_2->text();
    Client.Nazwisko = ui->lineEdit_nazwisko_2->text();
    Client.Adres = ui->lineEdit_adres_2->text();
    Client.NumerTelefonu = ui->lineEdit_nrtel_2->text().toInt();
    Client.Email = ui->lineEdit_email_2->text();

    if (Db->addNewClient(Client.Imie, Client.Nazwisko, Client.Adres, Client.NumerTelefonu, Client.Email)) {
        Client.ClientID = Db->clientDataHandler(clientColumn::ID,-1).integer;
        Client.NumerKarty = Db->clientDataHandler(clientColumn::CARD_NUM,-1).integer;
        QMessageBox::information(this, "Information", "Record inserted successfully.");
        emit submitInput(Client);
    } else {
        QMessageBox::critical(this, "Error", "Failed to insert record into database.");
    }


}

//void addclientelement::on_pushButton_dodajKlienta_2_clicked()
//    {


//            fprintf(stdout, "Opened database successfully\n");
//            QString imie = ui->lineEdit_imie_2->text();
//            QString nazwisko = ui->lineEdit_nazwisko_2->text();
//            QString adres = ui->lineEdit_adres_2->text();
//            int nrtel = ui->lineEdit_nrtel_2->text().toInt();
//            QString email = ui->lineEdit_email_2->text();

//            if (Db->addNewClient(imie, nazwisko, adres, nrtel, email)) {
//                QMessageBox::information(this, "Information", "Record inserted successfully.");
//            } else {
//                QMessageBox::critical(this, "Error", "Failed to insert record into database.");
//            }


//}

addclientelement::~addclientelement(){
        delete ui;
        delete this->Db;
    }




