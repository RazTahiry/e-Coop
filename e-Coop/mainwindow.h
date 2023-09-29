#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_accueilBtn_clicked();

        void on_GestionTrajetBtn_clicked();

        void on_historiqueBtn_clicked();

        void on_aproposBtn_clicked();

        void on_homeIcon_clicked();

        void on_mapIcon_clicked();

        void on_historiqueIcon_clicked();

        void on_infoIcon_clicked();

        void on_quitterBtn_clicked();

        void on_quitIcon_clicked();

        void on_settingBtn_clicked();

        void on_ajoutVehiculeBtn_clicked();

        void on_validerCoop_clicked();

        void on_resetCoop_clicked();

        void on_majVehiculeBtn_clicked();

        void on_supprVehiculeBtn_clicked();

        void on_annulerVehiculeBtn_clicked();

        void on_majTrajetBtn_clicked();

        void on_ajoutTrajetBtn_clicked();

        void on_supprTrajetBtn_clicked();

        void on_annulerTrajetBtn_clicked();

        void on_reserver_clicked();

private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
