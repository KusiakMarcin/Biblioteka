#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Headers/ClientTableModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(ui->actiona->isChecked()){
        QHBoxLayout *layout = ui->horizontalLayout;
        QPushButton *button1 = new QPushButton("ione");
        layout->addWidget(button1);

    }



}

MainWindow::~MainWindow()
{
    delete ui;

}



