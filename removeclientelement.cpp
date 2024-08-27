#include "Headers/Clients.h"
#include "removeclientelement.h"
#include "ui_removeclientelement.h"

RemoveClientElement::RemoveClientElement(QWidget *parent, const Clients& client)
    : QDialog(parent), ui(new Ui::RemoveClientElement), confirmed(false) {

    RemoveClientElement ui;
    ui.setupUi(this);

    ui.labelInfo->setText(QString("Czy na pewno chcesz usunąć klienta o ID: %1?\n\n"
                                  "Imię: %2\nNazwisko: %3\nAdres: %4\nNr telefonu: %5\nEmail: %6")
                              .arg(client.ClientID)
                              .arg(client.Imie)
                              .arg(client.Nazwisko)
                              .arg(client.Adres)
                              .arg(client.NumerTelefonu)
                              .arg(client.Email));
}
