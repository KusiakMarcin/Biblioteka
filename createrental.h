#ifndef CREATERENTAL_H
#define CREATERENTAL_H

#include <QDialog>

namespace Ui {
class CreateRental;
}

class CreateRental : public QDialog
{
    Q_OBJECT

public:
    explicit CreateRental(QWidget *parent = nullptr);
    ~CreateRental();

private:
    Ui::CreateRental *ui;
};

#endif // CREATERENTAL_H
