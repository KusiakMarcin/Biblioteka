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
    connect(ui->clientadd,&QPushButton::clicked,this,&MainWindow::addClientDialog);
    isRentalTable();
    connect(ui->clientdelete, &QPushButton::clicked, this, &MainWindow::removeClientDialog);
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

    if (!current.isValid()) return false;
    SelectedClient = current;
    qDebug()<<SelectedClient;
    /*int row = current.row();
    SelectedClientData.ClientID = ClientModel->data(ClientModel->index(row, 0)).toInt();
    SelectedClientData.Imie = ClientModel->data(ClientModel->index(row, 1)).toString();
    SelectedClientData.Nazwisko = ClientModel->data(ClientModel->index(row, 2)).toString();
    SelectedClientData.Adres = ClientModel->data(ClientModel->index(row, 3)).toString();
    SelectedClientData.NumerTelefonu = ClientModel->data(ClientModel->index(row, 4)).toInt();
    SelectedClientData.Email = ClientModel->data(ClientModel->index(row, 5)).toString();
    qDebug() << "Selected Client ID:" << SelectedClientData.ClientID;*/
    //if(SelectedClient!=previous)
    int clientId = ClientModel->data(ClientModel->index(current.row(), 0)).toInt();
    SelectedClientData.ClientID = clientId;
    SelectedClientData.Imie = ClientModel->data(ClientModel->index(current.row(), 1)).toString();
    SelectedClientData.Nazwisko = ClientModel->data(ClientModel->index(current.row(), 2)).toString();
    SelectedClientData.Adres = ClientModel->data(ClientModel->index(current.row(), 3)).toString();
    SelectedClientData.NumerTelefonu = ClientModel->data(ClientModel->index(current.row(), 4)).toInt();
    SelectedClientData.Email = ClientModel->data(ClientModel->index(current.row(), 5)).toString();
    qDebug() << "Selected Client ID:" << SelectedClientData.ClientID;
    if (SelectedClient != previous) return true;
    return false;
    //    return true;

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

void MainWindow::removeClientDialog()
{
    if (!SelectedClient.isValid()) return;

    RemoveClientElement dialog(this, SelectedClientData);
    if (dialog.exec() == QDialog::Accepted && dialog.isConfirmed()) {
        int row = SelectedClient.row();
        ClientModel->deleteElement(row);
    }
}
