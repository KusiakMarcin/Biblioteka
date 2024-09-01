#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Headers/ClientTableModel.h"
#include "Headers/BooksTableModel.h"
#include "Headers/RentalsTableModel.h"
#include "Headers/database.h"
#include "editclient.h"
#include <QMainWindow>
#include "QTableView"
#include "addclientelement.h"
#include "addbookelement.h"
#include "createrental.h"
#include <QSortFilterProxyModel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setupClientTable();
    void setupBookTable();
    void setupRentalTable();
    ~MainWindow();



public slots:



    //int addClientTable();
    //int addBooksTable();

private slots:

    bool updateSelectedClient(const QModelIndex &current,const QModelIndex &previous);
    bool updateSelectedBook(const QModelIndex &current,const QModelIndex &previous);
    void addClientDialog();
    void addRentalDialog();
    void editClientDialog();
    void resetClient();
    void resetBook();
    void deleteClient();
    void deleteBook();
    void addBookDialog();

private:
    Ui::MainWindow *ui;
    database *Db = new database;                            //strumien do bazy danych
    ClientTableModel *ClientModel = new ClientTableModel(Db,this);
    BooksTableModel *BookModel = new BooksTableModel(Db,this);
    RentalsTableModel *RentalModel = new RentalsTableModel(Db,this);
    QTableView *ClientTable = new QTableView(this);
    QTableView *BooksTable = new QTableView(this);
    QTableView *RentalTable = new QTableView(this);
    addclientelement *dialogAddClient = new addclientelement(Db, this);
    addbookelement *dialogBook = new addbookelement(Db,this);
    CreateRental *dialogRental = new CreateRental(Db,this);
    editclient *dialogEditClient = new editclient(Db,this);





    QModelIndex SelectedClient;
    QModelIndex SelectedBook;
    QModelIndex SelectedRental;
    QSortFilterProxyModel *proxyModelClient = new QSortFilterProxyModel;
    QSortFilterProxyModel *proxyModelBook = new QSortFilterProxyModel;
    QSortFilterProxyModel *proxyModelRental = new QSortFilterProxyModel;
};
#endif // MAINWINDOW_H
