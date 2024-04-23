#include "addclientelement.h"
#include "ui_addclientelement.h"

AddClientElement::AddClientElement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClientElement)
{
    ui->setupUi(this);
}

AddClientElement::~AddClientElement()
{
    delete ui;
}
