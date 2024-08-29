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

    proxyModel->setSourceModel(ClientModel);
    proxyModel->setFilterKeyColumn(-1);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    connect(ui->clientSerach, &QLineEdit::textChanged,proxyModel,&QSortFilterProxyModel::setFilterFixedString);
    ClientTable->setModel(proxyModel);
    ClientTable->setSortingEnabled(true);
    ClientTable->resizeColumnsToContents();
    ui->clientLayout->addWidget(ClientTable);
    connect(ClientTable->selectionModel(),&QItemSelectionModel::currentChanged,this,&MainWindow::updateSelectedClient);
    connect(ui->clientdelete,&QPushButton::clicked,this,&MainWindow::deleteClient);
    connect(dialogClient,&addclientelement::submitedClient,this,&MainWindow::addClient);


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

void MainWindow::deleteClient(){
    qDebug()<<ClientModel->rowCount();
    qDebug()<<"index:"<<SelectedClient.row();
    int ID = ui->clientDelete->text().toInt();
    qDebug()<<"ID:"<<ID;
    Db->removeClient(ID);
    ClientModel->resetModel();

}



void MainWindow::addClientDialog(){
    dialogClient->show();
    //ClientTable->setSortingEnabled(false);
}
void MainWindow::addClient(){
    //ClientTable->setSortingEnabled(true);
    ClientModel->resetModel();
}

void MainWindow::addBookDialog(){
    dialogBook->show();
}

