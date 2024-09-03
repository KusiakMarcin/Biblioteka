#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QItemSelectionModel>
#include <QMessageBox>

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
    connect(ui->bookedit,&QPushButton::clicked,this,&MainWindow::editBookDialog);
    connect(ui->bookdelete,&QPushButton::clicked,this,&MainWindow::deleteBook);

    connect(ui->rentaladd,&QPushButton::clicked,this,&MainWindow::addRentalDialog);
    connect(ui->rentaldelete,&QPushButton::clicked,this,&MainWindow::deleteRental);
    connect(ui->rentaledit,&QPushButton::clicked,this,&MainWindow::editRentalDialog);
    setStatusBar(nullptr);

    connect(dialogEditRental,&editrental::parseClientID,ClientModel,&ClientTableModel::runCheck);
    connect(ClientModel,&ClientTableModel::returnClient,dialogEditRental,&editrental::ifClientExists);

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
    connect(dialogEditClient,&editclient::dataEdited,this,&MainWindow::resetClient);



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
    connect(dialogEditBook,&editbook::dataEdited,this,&MainWindow::resetBook);
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
    connect(dialogRental,&CreateRental::dataSubmited,this,&MainWindow::resetRental);
    connect(dialogEditRental,&editrental::dataEdited,this,&MainWindow::resetRental);

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
    if(ID==0){QMessageBox::information(this,"Error","Incorrect input");}
    else {Db->removeClient(ID);

        ClientModel->resetModel();}

}
void MainWindow::deleteBook(){
    int ID = ui->bookDelete->text().toInt();
    if(ID==0){QMessageBox::information(this,"Error","Incorrect input");}
    else {Db->removeBook(ID);
        BookModel->resetModel();}

}

void MainWindow::deleteRental(){
    int ID = ui->rentalDelete->text().toInt();
    if(ID==0)QMessageBox::information(this,"Error","Incorrect input");
    else {Db->removeRental(ID);
        RentalModel->resetModel();}
}


void MainWindow::editClientDialog(){
    Clients client = ClientModel->findClient(ui->clientEdit->text().toInt());
    if(client.ClientID!=0){
    dialogEditClient->parseClient(client);
    dialogEditClient->show();
    }
    else{QMessageBox::information(this,"Error","No client with such ID");}


}

void MainWindow::editBookDialog(){
    Books book = BookModel->findBook(ui->bookEdit->text().toInt());
    if(book.BookID!=0){
    dialogEditBook->parseBook(book);
    dialogEditBook->show();
    }
    else{QMessageBox::information(this,"Error","No book with such ID");}
}

void MainWindow::editRentalDialog(){
    Rentals rental = RentalModel->findRental(ui->rentalEdit->text().toInt());
    if(rental.ID!=0){
    dialogEditRental->parseRental(rental);
    dialogEditRental->show();
    }
    else{QMessageBox::information(this,"Error","No rental with such ID");}
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

void MainWindow::resetRental(){
    RentalModel->resetModel();
}





