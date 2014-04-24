#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication colorManipulation(argc,argv);
    MainWindow mainwindow;
    mainwindow.show();
    return colorManipulation.exec();
}


