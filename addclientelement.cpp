#include "addclientelement.h"
#include "ui_addclientelement.h"

addclientelement::addclientelement(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addclientelement)
{
    ui->setupUi(this);
}

addclientelement::~addclientelement()
{
    delete ui;
}
