#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Headers/ClientTableModel.h"
#include "Headers/BooksTableModel.h"
#include "addclientelement.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    isClientTable();
    isBooksTable();


}

int MainWindow::isClientTable(){



    QHBoxLayout *layout = ui->horizontalLayout;
    ClientTableModel *Model = new ClientTableModel;
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




MainWindow::~MainWindow(){
    delete ui;

}



void MainWindow::on_addclient_clicked(){

    addclientelement *dialog = new addclientelement(this);
    dialog->show();

}

