#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("e-Coop (Beta - version)");
    QIcon appIcon(":/Icons/Bold Icons/logoecoop.ico");
    w.setWindowIcon(appIcon);
    w.show();
    return a.exec();
}
