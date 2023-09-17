#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QWidget *centralWidget = new QWidget(&w);
    w.setWindowTitle("e-Coop");
    w.show();
    return a.exec();
}
