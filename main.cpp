#include "mainwindow.h"
#include <QApplication>
#include "Headers/sqlite3.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
 /*   int rc;
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
    }*/


    return a.exec();
}
