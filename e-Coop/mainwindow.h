#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QStandardItemModel>
#include <QTableWidgetItem>

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

        void affichage_par_defaut_sur_MainWindow();

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

        void on_gestionBtn_clicked();

        void on_gestionIcon_clicked();

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

        void on_pushButton_clicked();

        void on_annulerReserve_clicked();

        void on_annulerVerifBtn_clicked();

        void on_parDefaut_clicked();

        void on_gerer_clicked();

        void on_stackedWidget_currentChanged(int index);

        void on_refTrajet_2_currentTextChanged(const QString &arg1);

        void on_verifierTrajet_clicked();

        void on_trajetGestionTableView_itemClicked(QTableWidgetItem *item);

        void on_trajetReservationTableView_itemClicked(QTableWidgetItem *item);

        void on_vehiculeGestionTableView_itemClicked(QTableWidgetItem *item);

        void on_trajetGestionTableView_itemSelectionChanged();

        void on_vehiculeGestionTableView_itemSelectionChanged();

        void on_lieuDepart_currentTextChanged(const QString &arg1);

        void on_lieuArrive_currentTextChanged(const QString &arg1);

        void on_majReservationBtn_clicked();

        void on_reservationTableView_itemClicked(QTableWidgetItem *item);

        void on_supprReservationBtn_clicked();

        void on_vehiculeCombobox_2_currentTextChanged(const QString &arg1);

        void on_heureCombobox_2_currentTextChanged(const QString &arg1);

        void on_dateFiltre_dateChanged(const QDate &date);

        void on_searchInput_4_textChanged(const QString &arg1);

private:
        Ui::MainWindow *ui;

        bool isMouseDown = false;

        QStandardItemModel *model;
};
#endif // MAINWINDOW_H
