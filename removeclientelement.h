#ifndef REMOVECLIENTELEMENT_H
#define REMOVECLIENTELEMENT_H

#include <QDialog>
#include "Headers/Clients.h"
#include "Headers/database.h"

namespace Ui {
class RemoveClientElement;
}

class RemoveClientElement : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveClientElement(QWidget *parent = nullptr, const Clients& client = Clients());
    ~RemoveClientElement();

    bool isConfirmed() const;

private slots:
    void on_ButtonConfirm_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::RemoveClientElement *ui;
    database* Db;
    Clients clientData;
    bool confirmed;
};

#endif // REMOVECLIENTELEMENT_H
