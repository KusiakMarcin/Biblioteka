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
    int rc;
    rc = sqlite3_initialize();
    if ( rc != SQLITE_OK )
    {
        fprintf(stderr, "Can't initialize sqlite: %s\n", sqlite3_errmsg(Db));
    }
    int dbc = sqlite3_open("Data.db", &Db);
    if (dbc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(Db));
    }
    else {
        fprintf(stdout, "Opened database successfully\n");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

void MainWindow::on_pushButton_clicked()
{
    //tylko do sprawdzenia poprawnosci dzialania kwerendy przy nacisnieciu przycisku
    //mozna skasowac jesli przeszkadza
    /*char* messaggeError;
    const char* sql = "INSERT INTO Klienci VALUES (NULL, 'Jerzy', 'Mazue', 'Szoszowa 13/13, 05-075 Warszawa', 511465892, 'jsliwek@essa.com', 00000003);";
    int rc = sqlite3_exec(Db, sql, callback, 0, &messaggeError);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", messaggeError);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(Db);*/
}


void MainWindow::on_pushButton_2_clicked()
{

}


void MainWindow::on_pushButton_3_clicked()
{

}

