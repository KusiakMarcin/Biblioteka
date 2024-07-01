#include "mainwindow.h"
#include <QApplication>
#include "Headers/sqlite3.h"
#include "Headers/database.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();








    return a.exec();
}
