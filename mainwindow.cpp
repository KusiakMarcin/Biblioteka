#include "mainwindow.h"
#include "removeclientelement.h"
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

void MainWindow::removeClientDialog() {
    if (!SelectedClient.isValid()) {
        qDebug() << "No client selected.";
        return;
    }

    int clientID = SelectedClient.sibling(SelectedClient.row(), 0).data().toInt();
    QString clientName = SelectedClient.sibling(SelectedClient.row(), 1).data().toString();
    QString clientSurname = SelectedClient.sibling(SelectedClient.row(), 2).data().toString();
    QString clientAddress = SelectedClient.sibling(SelectedClient.row(), 3).data().toString();
    int clientPhone = SelectedClient.sibling(SelectedClient.row(), 4).data().toInt();
    QString clientEmail = SelectedClient.sibling(SelectedClient.row(), 5).data().toString();

    Clients client;
    client.ClientID = clientID;
    client.Imie = clientName;
    client.Nazwisko = clientSurname;
    client.Adres = clientAddress;
    client.NumerTelefonu = clientPhone;
    client.Email = clientEmail;

    RemoveClientElement dialog(this, client);
    if (dialog.exec() == QDialog::Accepted && dialog.isConfirmed()) {
        if (Db->removeClient(client.ClientID)) {
            qDebug() << "Client removed successfully.";
        } else {
            qDebug() << "Failed to remove client.";
        }
    }
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
