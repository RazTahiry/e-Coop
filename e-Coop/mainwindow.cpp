#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include "cooperative.h"
#include "reservation.h"
#include "vehicule.h"
#include "trajets.h"

#include <QMessageBox>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->iconMenubarContainer->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_accueilBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_homeIcon_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_GestionTrajetBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_mapIcon_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_historiqueBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_historiqueIcon_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_aproposBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::on_infoIcon_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_settingBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_quitterBtn_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Confirmation de sortie");
    msgBox.setText("Êtes-vous sûr de vouloir quitter l'application?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if (msgBox.exec() == QMessageBox::Yes) {
        QApplication::quit();
    }
}
void MainWindow::on_quitIcon_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Confirmation de sortie");
    msgBox.setText("Êtes-vous sûr de vouloir quitter l'application?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if (msgBox.exec() == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void MainWindow::on_validerCoop_clicked()
{
    QString nomCoop = ui->coopNom->text();
    QString contactCoop = ui->contactCoop->text();
    QString adresseCoop = ui->adresseCoop->text();
    Cooperative C;
    C.majCoop(nomCoop, contactCoop, adresseCoop);
}

void MainWindow::on_resetCoop_clicked()
{
    Cooperative C;
    C.reinitialiser();
}

void MainWindow::on_majVehiculeBtn_clicked()
{
    QString matriculation = ui->matriculation->text();
    int nbPlace = ui->placeSupportes->text().toInt();
    QString chauffeur = ui->chauffeur->text();
    QString contact1 = ui->contact_1->text();
    QString contact2 = ui->contact_2->text();
    Vehicule V;
    V.modifier_vehicule(matriculation,chauffeur,contact1,nbPlace);
}

void MainWindow::on_ajoutVehiculeBtn_clicked()
{
    QString matriculation = ui->matriculation->text();
    int nbPlace = ui->placeSupportes->text().toInt();
    QString chauffeur = ui->chauffeur->text();
    QString contact1 = ui->contact_1->text();
    QString contact2 = ui->contact_2->text();
    Vehicule V;
    V.ajouter_vehicule(matriculation,chauffeur,contact1,nbPlace);
}

void MainWindow::on_supprVehiculeBtn_clicked()
{
    QString matriculation = ui->matriculation->text();
    Vehicule V;
    V.supprimer_vehicule(matriculation);
}

void MainWindow::on_annulerVehiculeBtn_clicked()
{

}

void MainWindow::on_majTrajetBtn_clicked()
{
    QString lieuDepart = ui->lieuDepart->text();
    QString lieuArrive = ui->lieuArrive->text();
    QString heureDepart = ui->heureDepart->text();
    QString refTrajet = ui->referenceTrajet->text();
    Trajets T;
    T.maj_trajet(refTrajet,lieuDepart,lieuArrive,heureDepart);
}

void MainWindow::on_ajoutTrajetBtn_clicked()
{
    QString lieuDepart = ui->lieuDepart->text();
    QString lieuArrive = ui->lieuArrive->text();
    QString heureDepart = ui->heureDepart->text();
    QString refTrajet = ui->referenceTrajet->text();
    Trajets T;
    T.ajout_trajet(refTrajet, lieuDepart, lieuArrive, heureDepart);
}

void MainWindow::on_supprTrajetBtn_clicked()
{
    QString refTrajet = ui->referenceTrajet->text();
    Trajets T;
    T.supprimer_trajet(refTrajet);
}

void MainWindow::on_annulerTrajetBtn_clicked()
{

}

void MainWindow::on_reserver_clicked()
{
    QString nomPass = ui->nomInput_2->text();
    QString contactPass = ui->contactInput_2->text();
    QString cin = ui->cin_2->text();
    QString refPlace = ui->referencePlace->text();
    QString membreFamille = ui->membreFamille_2->currentText();
    QString contactFamille = ui->contactFamille_2->text();
    QString lieuDepart = ui->lieuDepartPass->currentText();
    QString destination = ui->destination_2->currentText();
    int nbPlace = ui->nombrePlace_2->text().toInt();

    Reservation R;
    //R.reserver(refPlace , nomPass, contactPass, cin, nbPlace, membreFamille, contactFamille);
}
