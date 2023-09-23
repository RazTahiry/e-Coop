#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ajoutvehicule.h"
#include "ajouttrajet.h"
#include "ajoutjoursvoyage.h"
#include "ajoutheurevoyage.h"
#include "connexionBD.h"

#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->iconMenubarContainer->hide();
    //connectingDatabase();
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

void MainWindow::on_reservationBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_reserveIcon_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_historiqueBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::on_historiqueIcon_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_aproposBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::on_infoIcon_clicked()
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

void MainWindow::on_ajoutVehBtn_clicked()
{
    ajoutVehicule addVehicule;
    addVehicule.setModal(true);
    addVehicule.setWindowTitle("Ajout des véhicules");
    /*if(connectingDatabase() == true)
    {
        qDebug() << "Database connected!";
    }
    else
    {
        qDebug() << "Database not connected!";
    }*/
    addVehicule.exec();
}

void MainWindow::on_ajoutTrajBtn_clicked()
{
    ajoutTrajet addTrajet;
    addTrajet.setModal(true);
    addTrajet.setWindowTitle("Ajout des trajets");
    addTrajet.exec();
}

void MainWindow::on_ajoutJourBtn_clicked()
{
    ajoutJoursVoyage addJours;
    addJours.setModal(true);
    addJours.setWindowTitle("Ajout de jour du voyage");
    addJours.exec();
}

void MainWindow::on_ajoutHeureBtn_clicked()
{
    ajoutHeureVoyage addHeure;
    addHeure.setModal(true);
    addHeure.setWindowTitle("Ajout d'heure de départ du voyage");
    addHeure.exec();
}
