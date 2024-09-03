#include "editbook.h"
#include "ui_editbook.h"


editbook::editbook(database *Db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editbook)
{
    this->Db = Db;
    authorModel = new comboBox(AUTHOR,Db);
    genreModel = new comboBox(GENRE,Db);
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&editbook::editElement);
}
void editbook::editElement(){
    if(ui->title->text()!=data.Title){
        data.Title=ui->title->text();
        Db->editElement(data.BookID,1,1,ui->title->text());
    }
    if(ui->release->text().toInt()!=data.RokWydania){
        data.RokWydania= ui->release->text().toInt();
        Db->editElement(data.BookID,1,4,ui->release->text().toInt());
    }
    if(ui->stock->text().toInt()!=data.Stock){
        data.Stock= ui->stock->text().toInt();
        Db->editElement(data.BookID,1,3,ui->stock->text().toInt());
    }
    if(ui->author->text()!=data.Author){
        data.Author=ui->author->text();
        Db->editElement(data.BookID,1,2,ui->author->text());
    }
    if(ui->genre->text()!=data.Genre){
        data.Genre=ui->genre->text();
        Db->editElement(data.BookID,1,5,ui->genre->text());
    }
    emit dataEdited();
}
void editbook::parseBook(Books book){
    data = book;
    ui->title->setText(book.Title);
    ui->release->setText(QString().setNum(book.RokWydania));
    ui->stock->setText(QString().setNum(book.Stock));
    ui->author->setText(book.Author);
    ui->genre->setText(book.Genre);

}

editbook::~editbook()
{
    delete ui;
}
