#include "removeclientelement.h"
#include "ui_removeclientelement.h"
#include "Headers/database.h"
#include "QMessageBox"

RemoveClientElement::RemoveClientElement(QWidget *parent, const Clients& client)
    : QDialog(parent), ui(new Ui::RemoveClientElement), Db(nullptr), clientData(client), confirmed(false) {

    ui->setupUi(this);

    // Set up the information about the client in the dialog
    ui->labelInfo->setText(QString("Czy na pewno chcesz usunąć klienta o ID: %1?\n\n"
                                   "Imię: %2\nNazwisko: %3\nAdres: %4\nNr telefonu: %5\nEmail: %6")
                               .arg(client.ClientID)
                               .arg(client.Imie)
                               .arg(client.Nazwisko)
                               .arg(client.Adres)
                               .arg(client.NumerTelefonu)
                               .arg(client.Email));
}




RemoveClientElement::~RemoveClientElement() {
    delete ui;
}

bool RemoveClientElement::isConfirmed() const {
    return confirmed;
}


void RemoveClientElement::on_ButtonCancel_clicked() {
    confirmed = false;
    reject();
}

void RemoveClientElement::on_ButtonConfirm_clicked()
{
    if (Db) {
        bool success = Db->removeClient(clientData.ClientID);
        if (success) {
            confirmed = true;
            accept();
        } else {
            QMessageBox::warning(this, "Błąd", "Nie udało się usunąć klienta z bazy danych.");
        }
    }
}
