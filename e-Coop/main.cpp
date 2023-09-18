#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets>
#include <QWidget>
#include <QFile>
#include <QtUiTools/QUiLoader>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("e-Coop");
    w.show();
    return a.exec();
}
