#ifndef ADDCLIENTELEMENT_H
#define ADDCLIENTELEMENT_H

#include <QDialog>

namespace Ui {
class addclientelement;
}

class addclientelement : public QDialog
{
    Q_OBJECT

public:
    explicit addclientelement(QWidget *parent = nullptr);
    ~addclientelement();

private:
    Ui::addclientelement *ui;
};

#endif // ADDCLIENTELEMENT_H
