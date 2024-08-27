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
#include "removeclientelement.h"
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
    ~MainWindow();



public slots:

    int isRentalTable();

    //int addClientTable();
    //int addBooksTable();

private slots:

    bool updateSelectedClient(const QModelIndex &current,const QModelIndex &previous);
    bool updateSelectedBook(const QModelIndex &current,const QModelIndex &previous);
    void addClientDialog();
    void addBookDialog();

    void removeClientDialog();

private:
    Ui::MainWindow *ui;
    database *Db = new database;                            //strumien do bazy danych
    ClientTableModel *ClientModel = new ClientTableModel(Db);
    QTableView *ClientTable = new QTableView(this);
    addclientelement *dialogClient = new addclientelement(Db, this);
    addbookelement *dialogBook = new addbookelement(Db,this);
  //  RemoveClientElement *dialogRemoveClient = new RemoveClientElement;
    BooksTableModel *BookModel = new BooksTableModel;
    QTableView *BooksTable = new QTableView(this);
    RentalsTableModel *RentalModel = new RentalsTableModel;
    QTableView *RentalTable = new QTableView(this);
    QModelIndex SelectedClient;
    QModelIndex SelectedBook;
    QModelIndex SelectedRental;
};
#endif // MAINWINDOW_H
