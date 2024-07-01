#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTableView"
#include <QItemSelectionModel>
#include "addclientelement.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isClientTable(Db);
    isBooksTable();
    isRentalTable();

}

int MainWindow::isClientTable(database *Db){


    QHBoxLayout *layout = ui->horizontalLayout;
    ClientTableModel *Model = new ClientTableModel(Db);
    QTableView *ClientTable = new QTableView(this);
    ClientTable->setModel(Model);
    layout->addWidget(ClientTable);

}

int MainWindow::isBooksTable(){


    QHBoxLayout *layout = ui->horizontalLayout;
    BooksTableModel *Model = new BooksTableModel;
    QTableView *BooksTable = new QTableView(this);
    BooksTable->setModel(Model);
    layout->addWidget(BooksTable);

}

int MainWindow::isRentalTable(){
    QVBoxLayout *layout = ui->verticalLayout;
    RentalsTableModel *Model = new RentalsTableModel;
    QTableView *RentalTable = new QTableView(this);
    RentalTable->setModel(Model);
    layout->addWidget(RentalTable);


}



MainWindow::~MainWindow(){
    delete ui;
    delete Db;

}







void MainWindow::on_addclient_clicked()
{
    addclientelement *dialog = new addclientelement(Db, this);
    dialog->show();
}

