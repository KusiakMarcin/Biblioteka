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
    isRentalTable();
    connect(ui->clientadd,&QPushButton::clicked,this,&MainWindow::addClientDialog);
    connect(ui->clientedit,&QPushButton::clicked,this,&MainWindow::editClientDialog);
    connect(ui->clientdelete,&QPushButton::clicked,this,&MainWindow::deleteClient);
    connect(ui->bookadd,&QPushButton::clicked,this,&MainWindow::addBookDialog);
    connect(ui->bookdelete,&QPushButton::clicked,this,&MainWindow::deleteBook);
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
    qDebug()<<ClientModel->rowCount();
    qDebug()<<"index:"<<SelectedClient.row();
    int ID = ui->clientDelete->text().toInt();
    qDebug()<<"ID:"<<ID;
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
void MainWindow::resetClient(){

    ClientModel->resetModel();
}

void MainWindow::resetBook(){

    BookModel->resetModel();
}



void MainWindow::addBookDialog(){
    dialogBook->show();
}

