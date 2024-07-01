#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Headers/ClientTableModel.h"
#include "Headers/BooksTableModel.h"
#include "Headers/RentalsTableModel.h"
#include "Headers/database.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    database *Db = new database;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    int isClientTable(database *Db);
    int isBooksTable();
    int isRentalTable();
    //int addClientTable();
    //int addBooksTable();

private slots:


    void on_addclient_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
