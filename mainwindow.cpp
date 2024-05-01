#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Headers/ClientTableModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ClientTableModel Clients;
    ui->Clients->setModel(&Clients);


}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_pushButton_clicked()
{

}


void MainWindow::on_pushButton_2_clicked()
{

}

