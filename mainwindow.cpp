#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Headers/ClientTableModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addTable,SIGNAL(toggled(bool)),this,SLOT(addTable()));


}

int MainWindow::addClientTable(){
    QHBoxLayout *layout = ui->horizontalLayout;
    ClientTableModel *Model = new ClientTableModel;
    QTableView *Table = new QTableView;
    Table->setModel(Model);
    if(ui->addTable->isChecked())layout->addWidget(Table);


}
int MainWindow::addBooksTable(){


}
MainWindow::~MainWindow()
{
    delete ui;

}


