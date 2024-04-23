#ifndef ADDCLIENTELEMENT_H
#define ADDCLIENTELEMENT_H

#include <QDialog>

namespace Ui {
class AddClientElement;
}

class AddClientElement : public QDialog
{
    Q_OBJECT

public:
    explicit AddClientElement(QWidget *parent = nullptr);
    ~AddClientElement();

private:
    Ui::AddClientElement *ui;
};

#endif // ADDCLIENTELEMENT_H
