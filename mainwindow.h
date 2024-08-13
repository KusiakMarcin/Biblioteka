#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Headers/ClientTableModel.h"
#include "Headers/BooksTableModel.h"
#include "Headers/RentalsTableModel.h"
#include "Headers/database.h"
#include <QMainWindow>
#include "QTableView"
#include "addclientelement.h"
#include "addbookelement.h"
#include <QAbstractItemModel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setupClientTable();
    ~MainWindow();



public slots:
    int isBooksTable();
    int isRentalTable();

    //int addClientTable();
    //int addBooksTable();

private slots:

    bool updateSelectedClient(const QModelIndex &current,const QModelIndex &previous);
    void on_addclient_clicked();
    void on_addbook_clicked();

private:
    Ui::MainWindow *ui;
    database *Db = new database;                            //strumien do bazy danych
    ClientTableModel *ClientModel = new ClientTableModel(Db);
    QTableView *ClientTable = new QTableView(this);
    addclientelement *dialogClient = new addclientelement(Db, this);
    addbookelement *dialog = new addbookelement(Db,this);
    QModelIndex SelectedClient;
    QModelIndex SelectedBook;
    QModelIndex SelectedRental;
};
#endif // MAINWINDOW_H
