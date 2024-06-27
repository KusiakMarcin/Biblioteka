#ifndef ADDBOOKELEMENT_H
#define ADDBOOKELEMENT_H

#include <QDialog>

namespace Ui {
class addbookelement;
}

class addbookelement : public QDialog
{
    Q_OBJECT

public:
    explicit addbookelement(QWidget *parent = nullptr);
    ~addbookelement();

private:
    Ui::addbookelement *ui;
};

#endif // ADDBOOKELEMENT_H
