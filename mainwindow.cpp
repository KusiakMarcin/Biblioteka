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
    setupRentalTable();
    connect(ui->clientadd,&QPushButton::clicked,this,&MainWindow::addClientDialog);
    connect(ui->clientedit,&QPushButton::clicked,this,&MainWindow::editClientDialog);
    connect(ui->clientdelete,&QPushButton::clicked,this,&MainWindow::deleteClient);
    connect(ui->bookadd,&QPushButton::clicked,this,&MainWindow::addBookDialog);
    connect(ui->bookdelete,&QPushButton::clicked,this,&MainWindow::deleteBook);
    connect(ui->rentaladd,&QPushButton::clicked,this,&MainWindow::addBookDialog);
    setStatusBar(nullptr);

    //connect(ClientTable->selectionModel(),&QItemSelectionModel::selectionChanged)

}


void MainWindow::setupClientTable(){

    proxyModelClient->setSourceModel(ClientModel);
    proxyModelClient->setFilterKeyColumn(-1);
    proxyModelClient->setFilterCaseSensitivity(Qt::CaseInsensitive);
    connect(ui->clientSerach, &QLineEdit::textChanged,proxyModelClient,&QSortFilterProxyModel::setFilterFixedString);
    ClientTable->setModel(proxyModelClient);
    ClientTable->setSortingEnabled(true);
    ClientTable->resizeColumnsToContents();
    ui->clientLayout->addWidget(ClientTable);

    connect(dialogAddClient,&addclientelement::submitedClient,this,&MainWindow::resetClient);


}

void MainWindow::setupBookTable(){

    proxyModelBook->setSourceModel(BookModel);
    proxyModelBook->setFilterKeyColumn(-1);
    proxyModelBook->setFilterCaseSensitivity(Qt::CaseInsensitive);
    connect(ui->bookSearch, &QLineEdit::textChanged,proxyModelBook,&QSortFilterProxyModel::setFilterFixedString);
    BooksTable->setModel(proxyModelBook);
    BooksTable->setSortingEnabled(true);
    BooksTable->resizeColumnsToContents();
    ui->bookLayout->addWidget(BooksTable);
    connect(dialogBook,&addbookelement::dataSubmited,this,&MainWindow::resetBook);
}

void MainWindow::setupRentalTable(){

    proxyModelRental->setSourceModel(RentalModel);
    proxyModelRental->setFilterKeyColumn(-1);
    proxyModelRental->setFilterCaseSensitivity(Qt::CaseInsensitive);
    connect(ui->rentalSearch, &QLineEdit::textChanged,proxyModelRental,&QSortFilterProxyModel::setFilterFixedString);
    RentalTable->setModel(proxyModelRental);
    RentalTable->setSortingEnabled(true);
    RentalTable->resizeColumnsToContents();
    ui->rentalLayout->addWidget(RentalTable);
    //connect(dialogBook,&addbookelement::dataSubmited,this,&MainWindow::resetBook);
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
    delete dialogAddClient;
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
    int ID = ui->clientDelete->text().toInt();
    Db->removeClient(ID);
    ClientModel->resetModel();

}
void MainWindow::deleteBook(){
    int ID = ui->bookDelete->text().toInt();
    Db->removeBook(ID);
    BookModel->resetModel();

}


void MainWindow::editClientDialog(){
    ClientModel->findClient(ui->clientEdit->text().toInt());
    dialogEditClient->show();
}
void MainWindow::addClientDialog(){
    dialogAddClient->show();

}

void MainWindow::addBookDialog(){
    dialogBook->show();
}

void MainWindow::addRentalDialog(){
    dialogRental->show();
}
void MainWindow::resetClient(){

    ClientModel->resetModel();
}

void MainWindow::resetBook(){

    BookModel->resetModel();
}





