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
    isBooksTable();
    isRentalTable();
    //connect(ClientTable->selectionModel(),&QItemSelectionModel::selectionChanged)

}


void MainWindow::setupClientTable(){
    ClientTable->setModel(ClientModel);
    ui->horizontalLayout->addWidget(ClientTable);
    connect(ClientTable->selectionModel(),&QItemSelectionModel::currentChanged,this,&MainWindow::updateSelectedClient);
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
    delete ClientModel;
    delete ClientTable;
    delete dialogClient;


}

bool MainWindow::updateSelectedClient(const QModelIndex &current,const QModelIndex &previous){
    SelectedClient = current;
    qDebug()<<SelectedClient;
    if(SelectedClient!=previous) return 1;
    else return 0;

}





void MainWindow::on_addclient_clicked()
{
 dialogClient->show();
}


void MainWindow::on_addbook_clicked()
{

    dialog->show();
}

