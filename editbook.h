#ifndef EDITBOOK_H
#define EDITBOOK_H
#include "Headers/comboBox.h"
#include <QDialog>
#include "Headers/database.h"
#include "Headers/Books.h"

namespace Ui {
class editbook;
}

class editbook : public QDialog
{
    Q_OBJECT

public:
    explicit editbook(database *Db, QWidget *parent = nullptr);
    void parseBook(Books book);
    void editElement();

    ~editbook();

signals:
    void dataEdited();

private:
    Ui::editbook *ui;
    database *Db;
    Books data;
    comboBox* authorModel;
    comboBox* genreModel;
};

#endif // EDITBOOK_H
