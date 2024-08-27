#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QItemSelectionModel>


#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupClientTable();
    setupBookTable();
    connect(ui->clientadd,&QPushButton::clicked,this,&MainWindow::addClientDialog);
    isRentalTable();
    //connect(ClientTable->selectionModel(),&QItemSelectionModel::selectionChanged)

}


void MainWindow::setupClientTable(){
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(ClientModel);
    ClientTable->setModel(proxyModel);
    ClientTable->setSortingEnabled(true);
    ClientTable->resizeColumnsToContents();
    ui->clientLayout->addWidget(ClientTable);
    connect(ClientTable->selectionModel(),&QItemSelectionModel::currentChanged,this,&MainWindow::updateSelectedClient);
}

void MainWindow::setupBookTable(){

    BooksTable->setModel(BookModel);
    ui->bookLayout->addWidget(BooksTable);
    connect(BooksTable->selectionModel(),&QItemSelectionModel::currentChanged,this,&MainWindow::updateSelectedBook);
}

int MainWindow::isRentalTable(){


    RentalTable->setModel(RentalModel);
    ui->rentalLayout->addWidget(RentalTable);


}



MainWindow::~MainWindow(){
    delete ui;
    delete Db;
    delete ClientModel;
    delete ClientTable;
    delete BookModel;
    delete BooksTable;
    delete RentalModel;
    delete RentalTable;
    delete dialogClient;
    delete dialogBook;

}

bool MainWindow::updateSelectedClient(const QModelIndex &current,const QModelIndex &previous){
    SelectedClient = current;
    qDebug()<<SelectedClient;
    if(SelectedClient!=previous) return 1;
    else return 0;

}

bool MainWindow::updateSelectedBook(const QModelIndex &current,const QModelIndex &previous){
    SelectedBook = current;
    qDebug()<<SelectedClient;
    if(SelectedClient!=previous) return 1;
    else return 0;

}





void MainWindow::addClientDialog(){
    dialogClient->show();
}


void MainWindow::addBookDialog(){
    dialogBook->show();
}

