#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QtSql>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSqlDatabase db;
    bool openDb()
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("database.db");
        if (db.open())
        {
            qDebug() << "Database connected...";
            return true;
        }
        else
        {
            qDebug() << "Database not connected...";
            return false;
        }
    }
    void closeDb()
    {
        db.close();
    }

private slots:
    void on_accueilBtn_clicked();

    void on_GestionTrajetBtn_clicked();

    void on_reservationBtn_clicked();

    void on_historiqueBtn_clicked();

    void on_aproposBtn_clicked();

    void on_homeIcon_clicked();

    void on_mapIcon_clicked();

    void on_reserveIcon_clicked();

    void on_historiqueIcon_clicked();

    void on_infoIcon_clicked();

    void on_quitterBtn_clicked();

    void on_quitIcon_clicked();

    void on_settingBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
