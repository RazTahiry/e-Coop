#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("e-Coop (Beta - version)");
    w.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.png"));
    w.show();
    return a.exec();
}
