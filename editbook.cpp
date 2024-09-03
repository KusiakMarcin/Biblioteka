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
    ui->author->setModel(authorModel);
    ui->genre->setModel(genreModel);
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
    if(ui->author->currentText()!=data.Author){
        data.Author=ui->author->currentText();
        Db->editElement(data.BookID,1,2,ui->author->currentIndex()+1);
    }
    if(ui->genre->currentText()!=data.Genre){
        data.Genre=ui->genre->currentText();
        Db->editElement(data.BookID,1,5,ui->genre->currentIndex()+1);
    }
    emit dataEdited();
}
void editbook::parseBook(Books book){
    data = book;
    ui->title->setText(book.Title);
    ui->release->setText(QString().setNum(book.RokWydania));
    ui->stock->setText(QString().setNum(book.Stock));
    ui->author->setCurrentText(book.Author);
    ui->genre->setCurrentText(book.Genre);

}

editbook::~editbook()
{
    delete ui;
}
