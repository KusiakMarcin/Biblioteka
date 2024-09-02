#include "addbookelement.h"
#include "ui_addbookelement.h"
#include <QDebug>
#include <QMessageBox>

addbookelement::addbookelement(database* Db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addbookelement)
{
    db = Db;
    authorModel = new comboBox(AUTHOR,db);
    genreModel = new comboBox(GENRE,db);
    ui->setupUi(this);
    ui->authorBox->setModel(authorModel);
    ui->genreBox->setModel(genreModel);
    connect(ui->pushButton,&QPushButton::clicked,this,&addbookelement::addElement);

}

void addbookelement::addElement(){
    const QString title = ui->editTitle->text();
    int AuthorID = ui->authorBox->currentIndex()+1;
    int genreID = ui->genreBox->currentIndex()+1;
    int release = ui->editRelease->text().toInt();
    int stock = ui->editStock->text().toInt();

    if(db->addNewBook(title,release,stock,AuthorID,genreID)){
        emit dataSubmited();
        QMessageBox::information(this, "Information", "Record inserted successfully.");
    }else{
        QMessageBox::critical(this, "Error", "Failed to insert record into database.");
    }
    //qDebug()<<"author"<<ui->authorBox->currentIndex();
    //qDebug()<<"genre"<<ui->genreBox->currentIndex();


}

addbookelement::~addbookelement()
{
    delete ui;
    delete db;
    delete authorModel;
    delete genreModel;

}
