#include "mainwindow.h"
#include <QApplication>
#include "Headers/sqlite3.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    sqlite3 *Db;
    sqlite3_open("Data.db",&Db);


    return a.exec();
}
