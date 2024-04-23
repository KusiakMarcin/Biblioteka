#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;

}





void MainWindow::on_pushButton_clicked()
{
    int i = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(i+1);
}


void MainWindow::on_pushButton_2_clicked()
{
    int i = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(i-1);
}

