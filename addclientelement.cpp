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
    QString imie = ui->lineEdit_imie_2->text();
    QString nazwisko = ui->lineEdit_nazwisko_2->text();
    QString adres = ui->lineEdit_adres_2->text();
    int nrtel = ui->lineEdit_nrtel_2->text().toInt();
    QString email = ui->lineEdit_email_2->text();

    if (Db->addNewClient(imie, nazwisko, adres, nrtel, email)) {
        QMessageBox::information(this, "Information", "Record inserted successfully.");
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
    }




