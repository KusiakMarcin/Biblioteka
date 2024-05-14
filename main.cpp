#include "mainwindow.h"
#include <QApplication>
#include "Headers/sqlite3.h"
#include "Headers/database.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    database db;
    if(db.initDatabase())
    {
        fprintf(stdout, "Opened database successfully\n");
    }
    else
    {
        fprintf(stderr, "Can't open database");
    }






    return a.exec();
}
