#include "mainwindow.h"

#include <QApplication>

int playerHealth = 50;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

