#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Headers/ClientTableModel.h"
#include "addclientelement.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->IsCLientVisible,SIGNAL(toggled(bool)),this,SLOT(isClientTable()));
    qDebug() << this->children();
}

int MainWindow::isClientTable(){

    if(ui->IsCLientVisible->isChecked()){
        QHBoxLayout *layout = ui->horizontalLayout;
        ClientTableModel *Model = new ClientTableModel;
        QTableView *ClientTable = new QTableView(this);
        ClientTable->setModel(Model);
        layout->addWidget(ClientTable);
        qDebug() << this->children();
        qDebug() << layout->children();
        }
    else{
        ;
    }
    }

//int MainWindow::addClientTable(){
//    QHBoxLayout *layout = ui->horizontalLayout;
//    ClientTableModel *Model = new ClientTableModel;
//    QTableView *Table = new QTableView;
//    Table->setModel(Model);
//    if(ui->IsCLientVisible->isChecked())layout->addWidget(Table);


//}

//int MainWindow::removeClientTable(){
//    QHBoxLayout *layout = ui->horizontalLayout;
//    ClientTableModel *Model = new ClientTableModel;
//    QTableView *Table = new QTableView;
//    Table->setModel(Model);
//    if(ui->IsCLientVisible->isChecked())layout->addWidget(Table);


//}
//int MainWindow::addBooksTable(){


//};
MainWindow::~MainWindow(){
    delete ui;

}



void MainWindow::on_addclient_clicked(){

    addclientelement *dialog = new addclientelement(this);
    dialog->show();

}

