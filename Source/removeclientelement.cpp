#include "Headers/removeclientelement.h"

#include "ui_addclientelement.h"
#include <QMessageBox>

removeclientelement::removeclientelement(database *Db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addclientelement)
{
    this->Db=Db;
    ui->setupUi(this);
}
