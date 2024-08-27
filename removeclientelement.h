#ifndef REMOVECLIENTELEMENT_H
#define REMOVECLIENTELEMENT_H
#include "Headers/database.h"
#include <QDialog>
#include "Headers/Clients.h"

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
    void onConfirm();
    void onCancel();

private:
    Ui::RemoveClientElement *ui;
    bool confirmed;
};

#endif // REMOVECLIENTELEMENT_H
