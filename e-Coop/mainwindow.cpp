#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include "cooperative.h"
#include "reservation.h"
#include "vehicule.h"
#include "trajets.h"
#include "gestiontrajet.h"

#include <QMessageBox>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->iconMenubarContainer->hide();
    //affichage_reservation();
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        QSqlQuery query0;
        query0.exec("SELECT nomCoop FROM COOPERATIVE WHERE refCoop = 1");
        if(query0.next())
        {
            QString nomCoop = query0.value(0).toString() ;
            ui->nomCooperativeParam->setText(nomCoop);
            ui->nomCoop->setText(nomCoop);
        }

        QSqlQuery query1;
        query1.exec("SELECT refTrajet, heure FROM TRAJET");
        while(query1.next())
        {
            QString refTrajet = query1.value(0).toString();
            QString heure = query1.value(1).toString();
            ui->refTrajet_2->addItem(refTrajet);
            ui->refTrajet->addItem(refTrajet);
            ui->refTrajetVehicule->addItem(refTrajet);
            ui->heureTrajet->addItem(heure);
            ui->heureCombobox_2->addItem(heure);
            ui->heureReserve->addItem(heure);
        }

        QSqlQuery query2;
        query2.exec("SELECT numMAT FROM VEHICULE");
        while(query2.next())
        {
            QString numMat = query2.value(0).toString();
            ui->vehicule->addItem(numMat);
            ui->vehiculeCombobox_2->addItem(numMat);
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }

    gestionTrajet g;
    g.gerer();

    ui->membreFamille_2->setItemData(0, QVariant(0), Qt::UserRole - 1);
    ui->refTrajetVehicule->setItemData(0, QVariant(0), Qt::UserRole - 1);
    ui->refTrajet_2->setItemData(0, QVariant(0), Qt::UserRole - 1);
    ui->heureTrajet->setItemData(0, QVariant(0), Qt::UserRole - 1);
    ui->vehicule->setItemData(0, QVariant(0), Qt::UserRole - 1);
    ui->refTrajet->setItemData(0, QVariant(0), Qt::UserRole - 1);
    ui->heureReserve->setItemData(0, QVariant(0), Qt::UserRole - 1);

    ui->dateVerify->setDate(QDate::currentDate());
    ui->dateVoyage->setDate(QDate::currentDate());
    ui->dateFiltre->setDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_accueilBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    /*QString bgColor = "background-color: rgb(44, 51, 51);";
    QString currentStyle = ui->accueilBtn->styleSheet();
    QString newStyle = currentStyle + bgColor;
    ui->accueilBtn->setStyleSheet(newStyle);*/
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

void MainWindow::on_gestionBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_gestionIcon_clicked()
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
    QString contact1 = ui->contact1->text();
    QString contact2 = ui->contact2->text();
    QString adresseCoop = ui->adresseCoop->text();
    QString datePremierVoyage = ui->datePremierVoyage->text();

    Cooperative C;
    C.majCoop(nomCoop, contactCoop, contact1, contact2, adresseCoop, datePremierVoyage);

    ui->nomCooperativeParam->setText(nomCoop);
    ui->nomCoop->setText(nomCoop);

    ui->coopNom->clear();
    ui->contactCoop->clear();
    ui->contact1->clear();
    ui->contact2->clear();
    ui->adresseCoop->clear();
    ui->datePremierVoyage->setDate(QDate::currentDate());
}

void MainWindow::on_pushButton_clicked()
{
    ui->coopNom->clear();
    ui->adresseCoop->clear();
    ui->contactCoop->clear();
    ui->contact1->clear();
    ui->contact2->clear();
}

void MainWindow::on_resetCoop_clicked()
{
    Cooperative C;
    C.reinitialiser();

    ui->nomCooperativeParam->setText("");
    ui->nomCoop->setText("");

    ui->coopNom->clear();
    ui->contactCoop->clear();
    ui->adresseCoop->clear();
}

void MainWindow::on_majVehiculeBtn_clicked()
{
    QString matriculation = ui->matriculation->text();
    QString chauffeur = ui->chauffeur->text();
    QString contact1 = ui->contact_1->text();
    QString refTrajetVehicule = ui->refTrajetVehicule->currentText();
    int nbPlace = ui->placeSupportes->text().toInt();

    Vehicule V;
    V.modifier_vehicule(matriculation,chauffeur,contact1,nbPlace,refTrajetVehicule);

    ui->matriculation->clear();
    ui->placeSupportes->setValue(0);
    ui->chauffeur->clear();
    ui->contact_1->clear();
    ui->refTrajetVehicule->setCurrentIndex(0);
}

void MainWindow::on_ajoutVehiculeBtn_clicked()
{
    QString matriculation = ui->matriculation->text();
    QString chauffeur = ui->chauffeur->text();
    QString contact1 = ui->contact_1->text();
    QString refTrajetVehicule = ui->refTrajetVehicule->currentText();
    int nbPlace = ui->placeSupportes->text().toInt();

    Vehicule V;
    V.ajouter_vehicule(matriculation,chauffeur,contact1,nbPlace,refTrajetVehicule);

    ui->vehicule->addItem(matriculation);
    ui->vehiculeCombobox_2->addItem(matriculation);

    ui->matriculation->clear();
    ui->placeSupportes->setValue(0);
    ui->chauffeur->clear();
    ui->contact_1->clear();
    ui->refTrajetVehicule->setCurrentIndex(0);
}

void MainWindow::on_supprVehiculeBtn_clicked()
{
    QString matriculation = ui->matriculation->text();

    Vehicule V;
    V.supprimer_vehicule(matriculation);

    ui->matriculation->clear();
    ui->placeSupportes->setValue(0);
    ui->chauffeur->clear();
    ui->contact_1->clear();
    ui->refTrajetVehicule->setCurrentIndex(0);
}

void MainWindow::on_annulerVehiculeBtn_clicked()
{
    ui->matriculation->clear();
    ui->placeSupportes->setValue(0);
    ui->chauffeur->clear();
    ui->contact_1->clear();
    ui->refTrajetVehicule->setCurrentIndex(0);
}

void MainWindow::on_majTrajetBtn_clicked()
{
    QTime heureParDefaut(0, 0);
    QString lieuDepart = ui->lieuDepart->text();
    QString lieuArrive = ui->lieuArrive->text();
    QString refTrajet = ui->referenceTrajet->text();
    QString heureMatin = ui->heureMatin_2->text();
    QString heureSoir = ui->heureSoir_2->text();
    int decalage = ui->decalage->text().toInt();

    Trajets T;
    T.maj_trajet(refTrajet,lieuDepart,lieuArrive,heureMatin,heureSoir,decalage);

    ui->lieuDepart->clear();
    ui->lieuArrive->clear();
    ui->heureMatin_2->setTime(heureParDefaut);
    ui->heureSoir_2->setTime(heureParDefaut);
    ui->referenceTrajet->clear();
}

void MainWindow::on_ajoutTrajetBtn_clicked()
{

    QTime heureParDefaut(0, 0);
    QString lieuDepart = ui->lieuDepart->text();
    QString lieuArrive = ui->lieuArrive->text();
    QString refTrajet = ui->referenceTrajet->text();
    QString heureMatin = ui->heureMatin_2->text();
    QString heureSoir = ui->heureSoir_2->text();
    int decalage = ui->decalage->text().toInt();

    Trajets T;
    T.ajout_trajet(refTrajet,lieuDepart,lieuArrive,heureMatin,heureSoir,decalage);

    ui->refTrajetVehicule->addItem(refTrajet);
    ui->refTrajet->addItem(refTrajet);
    ui->refTrajet_2->addItem(refTrajet);
    ui->heureTrajet->addItem(heureMatin);
    ui->heureCombobox_2->addItem(heureSoir);

    ui->lieuDepart->clear();
    ui->lieuArrive->clear();
    ui->heureMatin_2->setTime(heureParDefaut);
    ui->heureSoir_2->setTime(heureParDefaut);
    ui->referenceTrajet->clear();
}

void MainWindow::on_supprTrajetBtn_clicked()
{
    QTime heureParDefaut(0, 0);
    QString refTrajet = ui->referenceTrajet->text();

    Trajets T;
    T.supprimer_trajet(refTrajet);

    ui->lieuDepart->clear();
    ui->lieuArrive->clear();
    ui->heureMatin_2->setTime(heureParDefaut);
    ui->heureSoir_2->setTime(heureParDefaut);
    ui->referenceTrajet->clear();
}

void MainWindow::on_annulerTrajetBtn_clicked()
{
    QTime heureParDefaut(0, 0);
    ui->lieuDepart->clear();
    ui->lieuArrive->clear();
    ui->heureMatin_2->setTime(heureParDefaut);
    ui->heureSoir_2->setTime(heureParDefaut);
    ui->referenceTrajet->clear();
}

void MainWindow::on_reserver_clicked()
{
    QString nomPass = ui->nomInput_2->text();
    QString contactPass = ui->contactInput_2->text();
    QString cin = ui->cin_2->text();
    QString refPlace = ui->referencePlace->text();
    QString membreFamille = ui->membreFamille_2->currentText();
    QString contactFamille = ui->contactFamille_2->text();
    QString voiture = ui->vehicule->currentText();
    QString refTrajet = ui->refTrajet->currentText();
    QString dateVoyage = ui->dateVoyage->text();
    QString heureDepart = ui->heureReserve->currentText();
    int nbPlace = ui->nombrePlace_2->text().toInt();

    int indexPaye = ui->frais_2->currentIndex();
    bool isPaye;
    isPaye = false;
    if(indexPaye == 0)
    {
        isPaye = false;
    }
    else if(indexPaye == 1)
    {
        isPaye = true;
    }

    Reservation R;
    R.reserver(refPlace, nomPass, contactPass, cin, nbPlace, membreFamille, contactFamille, voiture, refTrajet, dateVoyage, heureDepart, isPaye);

    ui->nomInput_2->clear();
    ui->contactInput_2->clear();
    ui->cin_2->clear();
    ui->referencePlace->clear();
    ui->membreFamille_2->setCurrentIndex(0);
    ui->contactFamille_2->clear();
    ui->vehicule->setCurrentIndex(0);
    ui->refTrajet->setCurrentIndex(0);
    ui->dateVoyage->setDate(QDate::currentDate());
    ui->heureReserve->setCurrentIndex(0);
    ui->nombrePlace_2->setValue(0);
}

void MainWindow::on_annulerReserve_clicked()
{
    ui->nomInput_2->clear();
    ui->contactInput_2->clear();
    ui->cin_2->clear();
    ui->referencePlace->clear();
    ui->membreFamille_2->setCurrentIndex(0);
    ui->contactFamille_2->clear();
    ui->vehicule->setCurrentIndex(0);
    ui->refTrajet->setCurrentIndex(0);
    ui->dateVoyage->setDate(QDate::currentDate());
    ui->heureReserve->setCurrentIndex(0);
    ui->nombrePlace_2->setValue(0);
}

void MainWindow::affichage_reservation()
{
    QSqlQuery query;
    int row;
    row = 0;
    query.exec("SELECT refPlace, nomPass FROM RESERVATION");
    while (query.next()) {
        row = query.value(0).toInt();
    }

    model = new QStandardItemModel(row, 2);
    int ligne(0);
    query.exec("SELECT refPlace, nomPass FROM RESERVATION");
    while(query.next())
    {
        for (int i = 0; i < 2; i++)
        {
            QStandardItem *item = new QStandardItem(query.value(i).toString());
            model->setItem(ligne, i, item);
        }
        ligne++;
    }
    model->setHeaderData(0, Qt::Horizontal, "Place");
    model->setHeaderData(1, Qt::Horizontal, "Nom");

    ui->reservationTable->setModel(model);
}

void MainWindow::on_annulerVerifBtn_clicked()
{
    ui->refTrajet_2->setCurrentIndex(0);
    ui->dateVerify->setDate(QDate::currentDate());
    ui->heureTrajet->setCurrentIndex(0);
}

void MainWindow::on_parDefaut_clicked()
{
    ui->vehiculeCombobox_2->setCurrentIndex(0);
    ui->dateFiltre->setDate(QDate::currentDate());
    ui->heureCombobox_2->setCurrentIndex(0);
}

void MainWindow::on_gerer_clicked()
{
}

