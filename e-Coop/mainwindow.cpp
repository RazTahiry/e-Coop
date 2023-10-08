#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cooperative.h"
#include "dbmanager.h"
#include "gestiontrajet.h"
#include "reservation.h"
#include "trajets.h"
#include "vehicule.h"

#include <QMessageBox>
#include <QPushButton>
#include <QDebug>
#include <QSqlTableModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->iconMenubarContainer->hide();
    affichage_par_defaut_sur_MainWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::affichage_par_defaut_sur_MainWindow()
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        QSqlQuery query0;
        query0.exec("SELECT nomCoop, adresseCoop, contactCoop, contact1Coop, contact2Coop, datePremierVoyage FROM COOPERATIVE WHERE refCoop = 1");
        if(query0.next())
        {
            QString nomCoop = query0.value(0).toString();
            QString adresse = query0.value(1).toString();
            QString contact = query0.value(2).toString();
            QString contact1 = query0.value(3).toString();
            QString contact2 = query0.value(4).toString();
            QDate datePremierVoyage = query0.value(5).toDate();

            ui->coopNom->setText(nomCoop);
            ui->adresseCoop->setText(adresse);
            ui->contactCoop->setText(contact);
            ui->contact1->setText(contact1);
            ui->contact2->setText(contact2);
            ui->datePremierVoyage->setDate(datePremierVoyage);

            ui->nomCooperativeParam->setText(nomCoop);
            ui->nomCoop->setText(nomCoop);
        }

        QSqlQuery query1;
        query1.exec("SELECT refTrajet, heureMatin, heureSoir, lieuDepart, destination, decalageVoyage FROM TRAJET");
        while(query1.next())
        {
            QString refTrajet = query1.value(0).toString();
            QString heureMatin = query1.value(1).toString();
            QString heureSoir = query1.value(2).toString();
            QString lieuDepart = query1.value(3).toString();
            QString Destination = query1.value(4).toString();
            ui->refTrajet_2->addItem(refTrajet);
            ui->refTrajet->addItem(refTrajet);
            ui->refTrajetVehicule->addItem(refTrajet);
            ui->heureTrajet->addItem(heureMatin);
            ui->heureTrajet->addItem(heureSoir);
            ui->heureCombobox_2->addItem(heureMatin);
            ui->heureCombobox_2->addItem(heureSoir);
            ui->heureReserve->addItem(heureMatin);
            ui->heureReserve->addItem(heureSoir);

            ui->trajetGestionTableView->setColumnCount(3);

            for (int column = 0; column < ui->trajetGestionTableView->columnCount(); ++column)
            {
                ui->trajetGestionTableView->horizontalHeader()->setSectionResizeMode(column, QHeaderView::Stretch);
            }

            QString stylesheet = "QHeaderView::section {"
                                "   background-color: rgb(46, 79, 79);"
                                "   color: rgb(203, 228, 222);"
                                "   padding: 6px;"
                                "   border-width: 1px;"
                                "   font-size: 13px;"
                                "}";

            ui->trajetGestionTableView->horizontalHeader()->setStyleSheet(stylesheet);

            ui->trajetGestionTableView->horizontalHeader()->setStretchLastSection(true);

            ui->trajetGestionTableView->verticalHeader()->setVisible(false);
            ui->trajetGestionTableView->setHorizontalHeaderLabels(QStringList() << "Réference trajet" << "Départ/Destination" << "Destination/Départ");

            int row = ui->trajetGestionTableView->rowCount();
            ui->trajetGestionTableView->insertRow(row);
            ui->trajetGestionTableView->setItem(row, 0, new QTableWidgetItem(refTrajet));
            ui->trajetGestionTableView->setItem(row, 1, new QTableWidgetItem(lieuDepart));
            ui->trajetGestionTableView->setItem(row, 2, new QTableWidgetItem(Destination));

        }

        QSqlQuery query2;
        query2.exec("SELECT numMAT, chauffeur, nbPlace, refTrajet, contactChauffeur FROM VEHICULE");
        while(query2.next())
        {
            QString numMat = query2.value(0).toString();
            QString chauffeur = query2.value(1).toString();
            QString nbPlace = query2.value(2).toString();
            QString refTrajet = query2.value(3).toString();
            ui->vehicule->addItem(numMat);
            ui->vehiculeCombobox_2->addItem(numMat);

            ui->vehiculeGestionTableView->setColumnCount(4);

            for (int column = 0; column < ui->vehiculeGestionTableView->columnCount(); ++column)
            {
                ui->vehiculeGestionTableView->horizontalHeader()->setSectionResizeMode(column, QHeaderView::Stretch);
            }

            QString styleSheet = "QHeaderView::section {"
                                "   background-color: rgb(46, 79, 79);"
                                "   color: rgb(203, 228, 222);"
                                "   padding: 6px;"
                                "   border-width: 1px;"
                                "   font-size: 13px;"
                                "}";

            ui->vehiculeGestionTableView->horizontalHeader()->setStyleSheet(styleSheet);
            ui->vehiculeGestionTableView->horizontalHeader()->setStretchLastSection(true);

            ui->vehiculeGestionTableView->verticalHeader()->setVisible(false);
            ui->vehiculeGestionTableView->setHorizontalHeaderLabels(QStringList() << "N° Matriculation" << "Chauffeur" << "Place supportés" << "Réference trajet");

            int row = ui->vehiculeGestionTableView->rowCount();

            ui->vehiculeGestionTableView->insertRow(row);
            ui->vehiculeGestionTableView->setItem(row, 0, new QTableWidgetItem(numMat));
            ui->vehiculeGestionTableView->setItem(row, 1, new QTableWidgetItem(chauffeur));
            ui->vehiculeGestionTableView->setItem(row, 2, new QTableWidgetItem(nbPlace));
            ui->vehiculeGestionTableView->setItem(row, 3, new QTableWidgetItem(refTrajet));
        }

        QSqlQuery query3;
        query3.exec("SELECT numMAT, refTrajet, heure, lieuDepart, destination, dateVoyage FROM GESTION");
        while(query3.next())
        {
            QString numMAT = query3.value(0).toString();
            QString refTrajet = query3.value(1).toString();
            QString heure = query3.value(2).toString();
            QString lieuDepart = query3.value(3).toString();
            QString destination = query3.value(4).toString();
            QString dateVoyage = query3.value(5).toString();

            ui->accueilTableWidget->setColumnCount(6);

            for (int column = 0; column < ui->accueilTableWidget->columnCount(); ++column)
            {
                ui->accueilTableWidget->horizontalHeader()->setSectionResizeMode(column, QHeaderView::Stretch);
            }

            QString styleSheet = "QHeaderView::section {"
                                "   background-color: rgb(46, 79, 79);"
                                "   color: rgb(203, 228, 222);"
                                "   padding: 6px;"
                                "   border-width: 1px;"
                                "   font-size: 13px;"
                                "}";

            ui->accueilTableWidget->horizontalHeader()->setStyleSheet(styleSheet);
            ui->accueilTableWidget->horizontalHeader()->setStretchLastSection(true);

            ui->accueilTableWidget->verticalHeader()->setVisible(false);
            ui->accueilTableWidget->setHorizontalHeaderLabels(QStringList() << "N° Matriculation (Véhicule)" << "Réference trajet" << "Heure de départ" << "Lieu de départ" << "Lieu d'arrivé" << "Date");

            int row = ui->accueilTableWidget->rowCount();

            ui->accueilTableWidget->insertRow(row);
            ui->accueilTableWidget->setItem(row, 0, new QTableWidgetItem(numMAT));
            ui->accueilTableWidget->setItem(row, 1, new QTableWidgetItem(refTrajet));
            ui->accueilTableWidget->setItem(row, 2, new QTableWidgetItem(heure));
            ui->accueilTableWidget->setItem(row, 3, new QTableWidgetItem(lieuDepart));
            ui->accueilTableWidget->setItem(row, 4, new QTableWidgetItem(destination));
            ui->accueilTableWidget->setItem(row, 5, new QTableWidgetItem(dateVoyage));
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }

    //gestionTrajet g;
    //g.gerer();

    ui->trajetReservationTableView->setColumnCount(3);

    for (int column = 0; column < ui->trajetReservationTableView->columnCount(); ++column)
    {
        ui->trajetReservationTableView->horizontalHeader()->setSectionResizeMode(column, QHeaderView::Stretch);
    }

    QString styleSheet = "QHeaderView::section {"
                        "   background-color: rgb(46, 79, 79);"
                        "   color: rgb(203, 228, 222);"
                        "   padding: 6px;"
                        "   border-width: 1px;"
                        "   font-size: 13px;"
                        "}";

    ui->trajetReservationTableView->horizontalHeader()->setStyleSheet(styleSheet);
    ui->trajetReservationTableView->horizontalHeader()->setStretchLastSection(true);

    ui->trajetReservationTableView->verticalHeader()->setVisible(false);
    ui->trajetReservationTableView->setHorizontalHeaderLabels(QStringList() << "Voiture" << "Lieu de départ" << "Lieu d'arrivé");

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
    ui->datePremierVoyage->setDate(QDate::currentDate());

    ui->majTrajetBtn->setDisabled(true);
    ui->majVehiculeBtn->setDisabled(true);
    ui->supprTrajetBtn->setDisabled(true);
    ui->supprVehiculeBtn->setDisabled(true);

    ui->stackedWidget->setCurrentIndex(0);

    int index = ui->stackedWidget->currentIndex();
    on_stackedWidget_currentChanged(index);
}

void MainWindow::on_refTrajet_2_currentTextChanged(const QString &arg1)
{
    DbManager db1(pathToDB);
    if(db1.isOpen())
    {
        QSqlQuery queryHeure;
        ui->heureTrajet->clear();
        queryHeure.prepare("SELECT heureMatin, heureSoir FROM TRAJET WHERE refTrajet = :Reftrj");
        queryHeure.bindValue(":Reftrj", arg1);
        if(queryHeure.exec())
        {
            while(queryHeure.next())
            {
                QString heureMatin1 = queryHeure.value(0).toString();
                QString heureSoir1 = queryHeure.value(1).toString();
                ui->heureTrajet->addItem(heureMatin1);
                ui->heureTrajet->addItem(heureSoir1);
            }
        }
        else
        {
            qDebug() << "Query error:" << queryHeure.lastError().text();
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}

void MainWindow::on_stackedWidget_currentChanged(int index)
{
    if(index == 0)
    {
        QString style = ui->accueilBtn->styleSheet();
        QString stylesheet = ui->homeIcon->styleSheet();
        style += "background-color:  rgb(44, 51, 51);";
        stylesheet += "background-color:  rgb(44, 51, 51);";
        ui->accueilBtn->setStyleSheet(style);
        ui->homeIcon->setStyleSheet(stylesheet);
    }
    else
    {
        ui->accueilBtn->setStyleSheet("color: rgb(203, 228, 222);"
                                      "border: none;"
                                      "width: 410px;"
                                      "text-align: left;"
                                      "padding: 10px 0 10px 10px;"
                                      );
        ui->homeIcon->setStyleSheet("padding: 10px 0 10px 0;");
    }

    if(index == 4)
    {
        QString style1 = ui->gestionBtn->styleSheet();
        QString stylesheet1 = ui->gestionIcon->styleSheet();
        style1 += "background-color:  rgb(44, 51, 51);";
        stylesheet1 += "background-color:  rgb(44, 51, 51);";
        ui->gestionBtn->setStyleSheet(style1);
        ui->gestionIcon->setStyleSheet(stylesheet1);
    }
    else
    {
        ui->gestionBtn->setStyleSheet("color: rgb(203, 228, 222);"
                                      "border: none;"
                                      "width: 410px;"
                                      "text-align: left;"
                                      "padding: 10px 0 10px 10px;"
                                      );
        ui->gestionIcon->setStyleSheet("padding: 10px 0 10px 0;");
    }

    if(index == 1)
    {
        QString style2 = ui->GestionTrajetBtn->styleSheet();
        QString stylesheet2 = ui->mapIcon->styleSheet();
        style2 += "background-color:  rgb(44, 51, 51);";
        stylesheet2 += "background-color:  rgb(44, 51, 51);";
        ui->GestionTrajetBtn->setStyleSheet(style2);
        ui->mapIcon->setStyleSheet(stylesheet2);
    }
    else
    {
        ui->GestionTrajetBtn->setStyleSheet("color: rgb(203, 228, 222);"
                                            "border: none;"
                                            "width: 410px;"
                                            "text-align: left;"
                                            "padding: 10px 0 10px 10px;"
                                            );
        ui->mapIcon->setStyleSheet("padding: 10px 0 10px 0;");
    }

    if(index == 2)
    {
        QString style3 = ui->historiqueBtn->styleSheet();
        QString stylesheet3 = ui->historiqueIcon->styleSheet();
        style3 += "background-color:  rgb(44, 51, 51);";
        stylesheet3 += "background-color:  rgb(44, 51, 51);";
        ui->historiqueBtn->setStyleSheet(style3);
        ui->historiqueIcon->setStyleSheet(stylesheet3);
    }
    else
    {
        ui->historiqueBtn->setStyleSheet("color: rgb(203, 228, 222);"
                                         "border: none;"
                                         "width: 410px;"
                                         "text-align: left;"
                                         "padding: 10px 0 10px 10px;"
                                         );
        ui->historiqueIcon->setStyleSheet("padding: 10px 0 10px 0;");
    }

    if(index == 3)
    {
        QString style4 = ui->aproposBtn->styleSheet();
        QString stylesheet4 = ui->infoIcon->styleSheet();
        style4 += "background-color:  rgb(44, 51, 51);";
        stylesheet4 += "background-color:  rgb(44, 51, 51);";
        ui->aproposBtn->setStyleSheet(style4);
        ui->infoIcon->setStyleSheet(stylesheet4);
    }
    else
    {
        ui->aproposBtn->setStyleSheet("color: rgb(203, 228, 222);"
                                      "border: none;"
                                      "width: 410px;"
                                      "text-align: left;"
                                      "padding: 10px 0 10px 10px;"
                                      );
        ui->infoIcon->setStyleSheet("padding: 10px 0 10px 0;");
    }
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
    msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                         "color: rgb(203, 228, 222);"
                         "font-size: 13px;");

    msgBox.setButtonText(QMessageBox::Yes, "Oui");
    msgBox.setButtonText(QMessageBox::No, "Non");

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
    msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                         "color: rgb(203, 228, 222);"
                         "font-size: 13px;");

    msgBox.setButtonText(QMessageBox::Yes, "Oui");
    msgBox.setButtonText(QMessageBox::No, "Non");

    if (msgBox.exec() == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void MainWindow::on_validerCoop_clicked()
{

    QMessageBox msgBox;
    msgBox.setWindowTitle("");
    msgBox.setText("La coopérative a été mise à jour.");

    msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                         "color: rgb(203, 228, 222);"
                         "font-size: 13px;");
    msgBox.exec();

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
    QMessageBox msgBox;
    msgBox.setWindowTitle("Confirmation de réinitialisation");
    msgBox.setText("Cliquez sur 'Annuler' si vous n'êtes pas sûr de vouloir réinitialiser la coopérative."
                   " Si vous choisissez de continuer en cliquant sur 'Réinitialiser', notez que toutes les données de cette coopérative seront réinitialisées, y compris les trajets, les véhicules, les données des passagers, les historiques, etc.");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                         "color: rgb(203, 228, 222);"
                         "font-size: 13px;");

    msgBox.setButtonText(QMessageBox::Yes, "Réinitialiser");
    msgBox.setButtonText(QMessageBox::No, "Annuler");

    if (msgBox.exec() == QMessageBox::Yes)
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle("");
        msgBox.setText("Coopérative réinitialisée.");

        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                             "color: rgb(203, 228, 222);"
                             "font-size: 13px;");
        msgBox.exec();

        Cooperative C;
        C.reinitialiser();

        ui->nomCooperativeParam->setText("");
        ui->nomCoop->setText("");

        ui->coopNom->clear();
        ui->contactCoop->clear();
        ui->contact1->clear();
        ui->contact2->clear();
        ui->adresseCoop->clear();

        ui->trajetGestionTableView->clearContents();
        ui->trajetGestionTableView->setRowCount(0);
        ui->vehiculeGestionTableView->clearContents();
        ui->vehiculeGestionTableView->setRowCount(0);
        ui->accueilTableWidget->clearContents();
        ui->accueilTableWidget->setRowCount(0);
    }
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

    int selectedRow = ui->vehiculeGestionTableView->currentRow();

    QTableWidgetItem *itemMatriculation = new QTableWidgetItem(matriculation);
    QTableWidgetItem *itemchauffeur = new QTableWidgetItem(chauffeur);
    QTableWidgetItem *itemNbPlace = new QTableWidgetItem(QString::number(nbPlace));
    QTableWidgetItem *itemRefTrajet = new QTableWidgetItem(refTrajetVehicule);

    ui->vehiculeGestionTableView->setItem(selectedRow, 0, itemMatriculation);
    ui->vehiculeGestionTableView->setItem(selectedRow, 1, itemchauffeur);
    ui->vehiculeGestionTableView->setItem(selectedRow, 2, itemNbPlace);
    ui->vehiculeGestionTableView->setItem(selectedRow, 3, itemRefTrajet);

    ui->vehiculeGestionTableView->clearSelection();

    ui->vehiculeGestionTableView->update();
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

    int rowCount = ui->vehiculeGestionTableView->rowCount();
    ui->vehiculeGestionTableView->insertRow(rowCount);

    QTableWidgetItem *itemMatriculation = new QTableWidgetItem(matriculation);
    QTableWidgetItem *itemChauffeur = new QTableWidgetItem(chauffeur);
    QTableWidgetItem *itemRefTrajet = new QTableWidgetItem(refTrajetVehicule);
    QTableWidgetItem *itemNbPlace = new QTableWidgetItem(QString::number(nbPlace));

    ui->vehiculeGestionTableView->setItem(rowCount, 0, itemMatriculation);
    ui->vehiculeGestionTableView->setItem(rowCount, 1, itemChauffeur);
    ui->vehiculeGestionTableView->setItem(rowCount, 2, itemNbPlace);
    ui->vehiculeGestionTableView->setItem(rowCount, 3, itemRefTrajet);
}

void MainWindow::on_supprVehiculeBtn_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Confirmation de suppression");
    msgBox.setText("Cliquez sur 'Annuler' si vous n'êtes pas sûr de vouloir supprimer ce véhicule."
                   " Si vous choisissez de continuer en cliquant sur 'Supprimer'.");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                         "color: rgb(203, 228, 222);"
                         "font-size: 13px;");

    msgBox.setButtonText(QMessageBox::Yes, "Supprimer");
    msgBox.setButtonText(QMessageBox::No, "Annuler");

    if (msgBox.exec() == QMessageBox::Yes)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("");
        msgBox.setText("Véhicule supprimé.");

        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                             "color: rgb(203, 228, 222);"
                             "font-size: 13px;");
        msgBox.exec();

        QString matriculation = ui->matriculation->text();

        Vehicule V;
        V.supprimer_vehicule(matriculation);

        ui->matriculation->clear();
        ui->placeSupportes->setValue(0);
        ui->chauffeur->clear();
        ui->contact_1->clear();
        ui->refTrajetVehicule->setCurrentIndex(0);

        int selectedRow = ui->vehiculeGestionTableView->currentRow();
        if (selectedRow >= 0)
        {
            ui->vehiculeGestionTableView->removeRow(selectedRow);
        }

        int index1 = ui->vehiculeCombobox_2->findText(matriculation);

        if(index1 != -1)
        {
            ui->vehiculeCombobox_2->removeItem(index1);
        }
    }
}

void MainWindow::on_annulerVehiculeBtn_clicked()
{
    ui->matriculation->clear();
    ui->placeSupportes->setValue(0);
    ui->chauffeur->clear();
    ui->contact_1->clear();
    ui->refTrajetVehicule->setCurrentIndex(0);
    ui->vehiculeGestionTableView->clearSelection();
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

    int selectedRow = ui->trajetGestionTableView->currentRow();

    QTableWidgetItem *itemRefTrajet = new QTableWidgetItem(refTrajet);
    QTableWidgetItem *itemLieuDepart = new QTableWidgetItem(lieuDepart);
    QTableWidgetItem *itemLieuArrive = new QTableWidgetItem(lieuArrive);

    ui->trajetGestionTableView->setItem(selectedRow, 0, itemRefTrajet);
    ui->trajetGestionTableView->setItem(selectedRow, 1, itemLieuDepart);
    ui->trajetGestionTableView->setItem(selectedRow, 2, itemLieuArrive);

    ui->trajetGestionTableView->clearSelection();

    ui->trajetGestionTableView->update();
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
    ui->decalage->setValue(0);

    int rowCount = ui->trajetGestionTableView->rowCount();
    ui->trajetGestionTableView->insertRow(rowCount);

    QTableWidgetItem *itemRefTrajet = new QTableWidgetItem(refTrajet);
    QTableWidgetItem *itemLieuDepart = new QTableWidgetItem(lieuDepart);
    QTableWidgetItem *itemLieuArrive = new QTableWidgetItem(lieuArrive);

    ui->trajetGestionTableView->setItem(rowCount, 0, itemRefTrajet);
    ui->trajetGestionTableView->setItem(rowCount, 1, itemLieuDepart);
    ui->trajetGestionTableView->setItem(rowCount, 2, itemLieuArrive);
}

void MainWindow::on_supprTrajetBtn_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Confirmation de suppression");
    msgBox.setText("Cliquez sur 'Annuler' si vous n'êtes pas sûr de vouloir supprimer ce trajet."
                   " Si vous choisissez de continuer en cliquant sur 'Supprimer', notez que toutes les véhicules dans ce trajet seront aussi supprimés.");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                         "color: rgb(203, 228, 222);"
                         "font-size: 13px;");

    msgBox.setButtonText(QMessageBox::Yes, "Supprimer");
    msgBox.setButtonText(QMessageBox::No, "Annuler");

    if (msgBox.exec() == QMessageBox::Yes)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("");
        msgBox.setText("Trajet supprimé.");

        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                             "color: rgb(203, 228, 222);"
                             "font-size: 13px;");
        msgBox.exec();

        QTime heureParDefaut(0, 0);
        QString refTrajet = ui->referenceTrajet->text();

        Trajets T;
        T.supprimer_trajet(refTrajet);

        ui->lieuDepart->clear();
        ui->lieuArrive->clear();
        ui->heureMatin_2->setTime(heureParDefaut);
        ui->heureSoir_2->setTime(heureParDefaut);
        ui->referenceTrajet->clear();

        int index1 = ui->refTrajetVehicule->findText(refTrajet);
        int index2 = ui->refTrajet_2->findText(refTrajet);

        if(index1 != -1 || index2 != -1)
        {
            ui->refTrajetVehicule->removeItem(index1);
            ui->refTrajet_2->removeItem(index2);
        }

        int selectedRow = ui->trajetGestionTableView->currentRow();
        if (selectedRow >= 0)
        {
            ui->trajetGestionTableView->removeRow(selectedRow);
        }

        int columnIndex = 3;
        int rowCount = ui->vehiculeGestionTableView->rowCount();

        for(int i = 0; i < rowCount; i++)
        {
            QTableWidgetItem *item = ui->vehiculeGestionTableView->item(i, columnIndex);
            if(item && item->text() == refTrajet)
            {
                QTableWidgetItem *refTrajetVide = new QTableWidgetItem("");
                ui->vehiculeGestionTableView->setItem(i, columnIndex, refTrajetVide);
            }
        }
        ui->vehiculeGestionTableView->update();
    }
}

void MainWindow::on_annulerTrajetBtn_clicked()
{
    QTime heureParDefaut(0, 0);
    ui->lieuDepart->clear();
    ui->lieuArrive->clear();
    ui->heureMatin_2->setTime(heureParDefaut);
    ui->heureSoir_2->setTime(heureParDefaut);
    ui->referenceTrajet->clear();
    ui->decalage->setValue(0);
    ui->trajetGestionTableView->clearSelection();
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
    R.reserver(refPlace, nomPass, contactPass, cin, nbPlace, membreFamille,
               contactFamille, voiture, refTrajet, dateVoyage, heureDepart, isPaye);

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

void MainWindow::on_annulerVerifBtn_clicked()
{
    ui->refTrajet_2->setCurrentIndex(0);
    ui->dateVerify->setDate(QDate::currentDate());
    ui->heureTrajet->setCurrentIndex(0);
    ui->trajetReservationTableView->clearContents();
    ui->trajetReservationTableView->setRowCount(0);
    ui->vehicule->setCurrentIndex(0);
    ui->refTrajet->setCurrentIndex(0);
    ui->heureReserve->setCurrentIndex(0);
    ui->dateVoyage->setDate(QDate::currentDate());
}

void MainWindow::on_parDefaut_clicked()
{
    ui->vehiculeCombobox_2->setCurrentIndex(0);
    ui->dateFiltre->setDate(QDate::currentDate());
    ui->heureCombobox_2->setCurrentIndex(0);
}

void MainWindow::on_gerer_clicked()
{
    gestionTrajet g;
    g.gerer();
}

void MainWindow::on_verifierTrajet_clicked()
{
    DbManager db2(pathToDB);
    if(db2.isOpen())
    {
        ui->trajetReservationTableView->clearContents();
        ui->trajetReservationTableView->setRowCount(0);
        QString refTrajet = ui->refTrajet_2->currentText();
        QString heure = ui->heureTrajet->currentText();
        QDate date = ui->dateVerify->date();

        QSqlQuery queryVerify;
        queryVerify.prepare("SELECT numMAT, lieuDepart, destination FROM GESTION WHERE refTrajet = :refTrajet AND dateVoyage = :date AND heure = :heure");
        queryVerify.bindValue(":refTrajet", refTrajet);
        queryVerify.bindValue(":heure", heure);
        queryVerify.bindValue(":date", date);

        if(queryVerify.exec())
        {
            while(queryVerify.next())
            {
                QString numMAT = queryVerify.value(0).toString();
                QString lieuDepart = queryVerify.value(1).toString();
                QString destination = queryVerify.value(2).toString();

                int row = ui->trajetReservationTableView->rowCount();

                ui->trajetReservationTableView->insertRow(row);
                ui->trajetReservationTableView->setItem(row, 0, new QTableWidgetItem(numMAT));
                ui->trajetReservationTableView->setItem(row, 1, new QTableWidgetItem(lieuDepart));
                ui->trajetReservationTableView->setItem(row, 2, new QTableWidgetItem(destination));
            }
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}

void MainWindow::on_trajetGestionTableView_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();
    QTableWidgetItem* itemRefTrajet = ui->trajetGestionTableView->item(row, 0);
    QTableWidgetItem* itemLieuDepart = ui->trajetGestionTableView->item(row, 1);
    QTableWidgetItem* itemDestination = ui->trajetGestionTableView->item(row, 2);

    if(itemRefTrajet && itemLieuDepart && itemDestination)
    {
        ui->majTrajetBtn->setDisabled(false);
        ui->referenceTrajet->setDisabled(true);
        ui->supprTrajetBtn->setDisabled(false);
        ui->ajoutTrajetBtn->setDisabled(true);

        DbManager db3(pathToDB);
        if(db3.isOpen())
        {
            QString refTrajet = itemRefTrajet->text();
            QString lieuDepart = itemLieuDepart->text();
            QString destination = itemDestination->text();

            QSqlQuery queryAfficheTrajet;

            queryAfficheTrajet.prepare("SELECT heureMatin, heureSoir, decalageVoyage FROM TRAJET WHERE refTrajet = :Reftrj");
            queryAfficheTrajet.bindValue(":Reftrj", refTrajet);
            if(queryAfficheTrajet.exec())
            {
                while(queryAfficheTrajet.next())
                {
                    QTime heureMatin1 = queryAfficheTrajet.value(0).toTime();
                    QTime heureSoir1 = queryAfficheTrajet.value(1).toTime();
                    int decalage = queryAfficheTrajet.value(2).toInt();

                    ui->referenceTrajet->setText(refTrajet);
                    ui->lieuDepart->setText(lieuDepart);
                    ui->lieuArrive->setText(destination);
                    ui->heureMatin_2->setTime(heureMatin1);
                    ui->heureSoir_2->setTime(heureSoir1);
                    ui->decalage->setValue(decalage);
                }
            }
            else
            {
                qDebug() << "Query error:" << queryAfficheTrajet.lastError().text();
            }
        }
        else
        {
            qDebug() << "Database not opened.";
        }

    }
}

void MainWindow::on_trajetReservationTableView_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();
    QTableWidgetItem* itemNumMat = ui->trajetReservationTableView->item(row, 0);
    QTableWidgetItem* itemLieuDepart = ui->trajetReservationTableView->item(row, 1);
    QTableWidgetItem* itemDestination = ui->trajetReservationTableView->item(row, 2);

    if(itemNumMat && itemLieuDepart && itemDestination)
    {
        DbManager db4(pathToDB);
        if(db4.isOpen())
        {
            QString numMat = itemNumMat->text();
            QString lieuDepart = itemLieuDepart->text();
            QString destination = itemDestination->text();

            QSqlQuery queryReserve;

            queryReserve.prepare("SELECT refTrajet, heure, dateVoyage FROM GESTION WHERE numMAT = :numMat AND lieuDepart = :depart AND destination = :dest");
            queryReserve.bindValue(":numMat", numMat);
            queryReserve.bindValue(":depart", lieuDepart);
            queryReserve.bindValue(":dest", destination);

            if(queryReserve.exec())
            {
                while(queryReserve.next())
                {
                    QString refTrajet = queryReserve.value(0).toString();
                    QString heure = queryReserve.value(1).toString();
                    QDate date = queryReserve.value(2).toDate();

                    ui->vehicule->setCurrentText(numMat);
                    ui->refTrajet->setCurrentText(refTrajet);
                    ui->heureReserve->setCurrentText(heure);
                    ui->dateVoyage->setDate(date);
                }
            }
            else
            {
                qDebug() << "Query error:" << queryReserve.lastError().text();
            }
        }
        else
        {
            qDebug() << "Database not opened.";
        }

    }
}

void MainWindow::on_vehiculeGestionTableView_itemClicked(QTableWidgetItem *item)
{

    int row = item->row();
    QTableWidgetItem* itemNumMat = ui->vehiculeGestionTableView->item(row, 0);
    QTableWidgetItem* itemChauffeur = ui->vehiculeGestionTableView->item(row, 1);
    QTableWidgetItem* itemNbPlace = ui->vehiculeGestionTableView->item(row, 2);
    QTableWidgetItem* itemRefTrajet = ui->vehiculeGestionTableView->item(row, 3);

    if(itemNumMat && itemChauffeur && itemNbPlace && itemRefTrajet)
    {
        ui->majVehiculeBtn->setDisabled(false);
        ui->matriculation->setDisabled(true);
        ui->supprVehiculeBtn->setDisabled(false);
        ui->ajoutVehiculeBtn->setDisabled(true);

        DbManager db5(pathToDB);
        if(db5.isOpen())
        {
            QString numMat = itemNumMat->text();
            QString chauffeur = itemChauffeur->text();
            QString nbPlace = itemNbPlace->text();
            QString refTrajet = itemRefTrajet->text();

            QSqlQuery queryAfficheVehicule;

            queryAfficheVehicule.prepare("SELECT contactChauffeur FROM VEHICULE WHERE numMAT = :numMat");
            queryAfficheVehicule.bindValue(":numMat", numMat);
            if(queryAfficheVehicule.exec())
            {
                while(queryAfficheVehicule.next())
                {
                    QString contact = queryAfficheVehicule.value(0).toString();

                    ui->matriculation->setText(numMat);
                    ui->placeSupportes->setValue(nbPlace.toInt());
                    ui->chauffeur->setText(chauffeur);
                    ui->contact_1->setText(contact);
                    ui->refTrajetVehicule->setCurrentText(refTrajet);
                }
            }
            else
            {
                qDebug() << "Query error:" << queryAfficheVehicule.lastError().text();
            }
        }
        else
        {
            qDebug() << "Database not opened.";
        }
    }
}

void MainWindow::on_trajetGestionTableView_itemSelectionChanged()
{
    int selectedItemCount = ui->trajetGestionTableView->selectedItems().count();

    if(selectedItemCount == 0)
    {
        QTime heureParDefaut(0, 0);
        ui->referenceTrajet->clear();
        ui->lieuDepart->clear();
        ui->lieuArrive->clear();
        ui->heureMatin_2->setTime(heureParDefaut);
        ui->heureSoir_2->setTime(heureParDefaut);
        ui->decalage->setValue(0);

        ui->majTrajetBtn->setDisabled(true);
        ui->referenceTrajet->setDisabled(false);
        ui->supprTrajetBtn->setDisabled(true);
        ui->ajoutTrajetBtn->setDisabled(false);
    }
}

void MainWindow::on_vehiculeGestionTableView_itemSelectionChanged()
{
    int selectedItemCount = ui->trajetGestionTableView->selectedItems().count();

    if(selectedItemCount == 0)
    {
        ui->matriculation->clear();
        ui->placeSupportes->setValue(0);
        ui->chauffeur->clear();
        ui->contact_1->clear();
        ui->refTrajetVehicule->setCurrentIndex(0);

        ui->majVehiculeBtn->setDisabled(true);
        ui->matriculation->setDisabled(false);
        ui->supprVehiculeBtn->setDisabled(true);
        ui->ajoutVehiculeBtn->setDisabled(false);
    }
}
