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
#include <QApplication>

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
    //---- Tableau de verification de trajet
    ui->trajetReservationTableView->setColumnCount(4);

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
                        "   font-family: Bahnschrift SemiBold;"
                        "}";

    ui->trajetReservationTableView->horizontalHeader()->setStyleSheet(styleSheet);
    ui->trajetReservationTableView->horizontalHeader()->setStretchLastSection(true);

    ui->trajetReservationTableView->verticalHeader()->setVisible(false);
    ui->trajetReservationTableView->setHorizontalHeaderLabels(QStringList() << "Voiture" << "Lieu de départ" << "Lieu d'arrivé" << "Place disponible");
    //--------------------------------------

    //---- Tableau des passagers
    ui->reservationTableView->setColumnCount(6);

    for (int column = 0; column < ui->reservationTableView->columnCount(); ++column)
    {
        if(column == 0)
        {
            ui->reservationTableView->setColumnWidth(column, 25);
        }
        else
        {
            ui->reservationTableView->horizontalHeader()->setSectionResizeMode(column, QHeaderView::Stretch);
        }
    }

    QString style = "QHeaderView::section {"
                        "   background-color: rgb(46, 79, 79);"
                        "   color: rgb(203, 228, 222);"
                        "   padding: 6px;"
                        "   border-width: 1px;"
                        "   font-size: 13px;"
                        "   font-family: Bahnschrift SemiBold;"
                        "}";

    ui->reservationTableView->horizontalHeader()->setStyleSheet(style);
    ui->reservationTableView->horizontalHeader()->setStretchLastSection(true);
    ui->reservationTableView->verticalHeader()->setVisible(false);
    ui->reservationTableView->setHorizontalHeaderLabels(QStringList() << "Id" << "Réference Place" << "Nom" << "Nombre de place" << "Frais" << "Contact");
    //--------------------------------------

    //---- Liste des Trajets
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
                        "   font-family: Bahnschrift SemiBold;"
                        "}";

    ui->trajetGestionTableView->horizontalHeader()->setStyleSheet(stylesheet);

    ui->trajetGestionTableView->horizontalHeader()->setStretchLastSection(true);

    ui->trajetGestionTableView->verticalHeader()->setVisible(false);
    ui->trajetGestionTableView->setHorizontalHeaderLabels(QStringList() << "Réference trajet" << "Départ/Destination" << "Destination/Départ");
    //---------------------------------

    //---- Liste des Véhicules
    ui->vehiculeGestionTableView->setColumnCount(4);

    for (int column = 0; column < ui->vehiculeGestionTableView->columnCount(); ++column)
    {
        ui->vehiculeGestionTableView->horizontalHeader()->setSectionResizeMode(column, QHeaderView::Stretch);
    }

    QString styleSheet1 = "QHeaderView::section {"
                        "   background-color: rgb(46, 79, 79);"
                        "   color: rgb(203, 228, 222);"
                        "   padding: 6px;"
                        "   border-width: 1px;"
                        "   font-size: 13px;"
                        "   font-family: Bahnschrift SemiBold;"
                        "}";

    ui->vehiculeGestionTableView->horizontalHeader()->setStyleSheet(styleSheet1);
    ui->vehiculeGestionTableView->horizontalHeader()->setStretchLastSection(true);

    ui->vehiculeGestionTableView->verticalHeader()->setVisible(false);
    ui->vehiculeGestionTableView->setHorizontalHeaderLabels(QStringList() << "N° Matriculation" << "Chauffeur" << "Place supportés" << "Réference trajet");
    //-----------------------------------

    //---- Liste des trajes et des véhicules sur la page d'accueil
    ui->accueilTableWidget->setColumnCount(7);

    for (int column = 0; column < ui->accueilTableWidget->columnCount(); ++column)
    {
        ui->accueilTableWidget->horizontalHeader()->setSectionResizeMode(column, QHeaderView::Stretch);
    }

    QString styleSheet2 = "QHeaderView::section {"
                        "   background-color: rgb(46, 79, 79);"
                        "   color: rgb(203, 228, 222);"
                        "   padding: 6px;"
                        "   border-width: 1px;"
                        "   font-size: 13px;"
                        "   font-family: Bahnschrift SemiBold;"
                        "}";

    ui->accueilTableWidget->horizontalHeader()->setStyleSheet(styleSheet2);
    ui->accueilTableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->accueilTableWidget->verticalHeader()->setVisible(false);
    ui->accueilTableWidget->setHorizontalHeaderLabels(QStringList() << "Voiture" << "Réference trajet" << "Heure de départ" << "Lieu de départ" << "Lieu d'arrivé" << "Date" << "Place disponible");
    //-----------------------------------------------------------

    //---- Liste des historiques
    ui->historiqueTableWidget->setColumnCount(7);

    for (int column = 0; column < ui->historiqueTableWidget->columnCount(); ++column)
    {
        ui->historiqueTableWidget->horizontalHeader()->setSectionResizeMode(column, QHeaderView::Stretch);
    }

    QString styleSheetHistory = "QHeaderView::section {"
                        "   background-color: rgb(46, 79, 79);"
                        "   color: rgb(203, 228, 222);"
                        "   padding: 6px;"
                        "   border-width: 1px;"
                        "   font-size: 13px;"
                        "   font-family: Bahnschrift SemiBold;"
                        "}";

    ui->historiqueTableWidget->horizontalHeader()->setStyleSheet(styleSheetHistory);
    ui->historiqueTableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->historiqueTableWidget->verticalHeader()->setVisible(false);
    ui->historiqueTableWidget->setHorizontalHeaderLabels(QStringList() << "Voiture" << "Réference trajet" << "Heure de départ" << "Lieu de départ" << "Lieu d'arrivé" << "Date" << "Places occupés");
    //-----------------------------------------------------------

    DbManager db(pathToDB);
    if(db.isOpen())
    {
        QSqlQuery query0;
        query0.exec("SELECT nomCoop, adresseCoop, contactCoop, contact1Coop, contact2Coop, datePremierVoyage FROM COOPERATIVE WHERE refCoop = 1");
        while(query0.next())
        {
            QString nomCoop = query0.value(0).toString();
            QString adresse = query0.value(1).toString();
            QString contact = query0.value(2).toString();
            QString contact1 = query0.value(3).toString();
            QString contact2 = query0.value(4).toString();
            QString datePremierVoyage = query0.value(5).toString();

            ui->coopNom->setText(nomCoop);
            ui->adresseCoop->setText(adresse);
            ui->contactCoop->setText(contact);
            ui->contact1->setText(contact1);
            ui->contact2->setText(contact2);
            ui->datePremierVoyage->setDate(QDate::fromString(datePremierVoyage, "dd/MM/yyyy"));

            ui->nomCooperativeParam->setText(nomCoop);
            ui->nomCoop->setText(nomCoop);

            if(nomCoop.isEmpty() && adresse.isEmpty())
            {
                ui->resetCoop->setDisabled(true);
                ui->ajoutTrajetBtn->setDisabled(true);
            }
            else if(!nomCoop.isEmpty() && !adresse.isEmpty())
            {
                ui->resetCoop->setDisabled(false);
                ui->ajoutTrajetBtn->setDisabled(false);
            }
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
            ui->refTrajetVehicule->addItem(refTrajet);
            ui->heureTrajet->addItem(heureMatin);
            ui->heureTrajet->addItem(heureSoir);
            ui->heureCombobox_2->addItem(heureMatin);
            ui->heureCombobox_2->addItem(heureSoir);

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
            ui->vehiculeCombobox_2->addItem(numMat);

            int row = ui->vehiculeGestionTableView->rowCount();

            ui->vehiculeGestionTableView->insertRow(row);
            ui->vehiculeGestionTableView->setItem(row, 0, new QTableWidgetItem(numMat));
            ui->vehiculeGestionTableView->setItem(row, 1, new QTableWidgetItem(chauffeur));
            ui->vehiculeGestionTableView->setItem(row, 2, new QTableWidgetItem(nbPlace));
            ui->vehiculeGestionTableView->setItem(row, 3, new QTableWidgetItem(refTrajet));
            ui->gerer->setDisabled(false);            
        }

        QSqlQuery query3;
        query3.exec("SELECT numMAT, refTrajet, heure, lieuDepart, destination, dateVoyage, placeDispo FROM GESTION");
        while(query3.next())
        {
            QString numMAT = query3.value(0).toString();
            QString refTrajet = query3.value(1).toString();
            QString heure = query3.value(2).toString();
            QString lieuDepart = query3.value(3).toString();
            QString destination = query3.value(4).toString();
            QDate dateVoyage = query3.value(5).toDate();
            int placeDispo = query3.value(6).toInt();

            if((dateVoyage >= QDate::currentDate()) && (dateVoyage <= QDate::currentDate().addDays(8)))
            {
                int row = ui->accueilTableWidget->rowCount();

                ui->accueilTableWidget->insertRow(row);
                ui->accueilTableWidget->setItem(row, 0, new QTableWidgetItem(numMAT));
                ui->accueilTableWidget->setItem(row, 1, new QTableWidgetItem(refTrajet));
                ui->accueilTableWidget->setItem(row, 2, new QTableWidgetItem(heure));
                ui->accueilTableWidget->setItem(row, 3, new QTableWidgetItem(lieuDepart));
                ui->accueilTableWidget->setItem(row, 4, new QTableWidgetItem(destination));
                ui->accueilTableWidget->setItem(row, 5, new QTableWidgetItem(dateVoyage.toString()));
                ui->accueilTableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(placeDispo)));
            }
            if(dateVoyage < QDate::currentDate())
            {
                QSqlQuery queryPlace;
                queryPlace.prepare("SELECT nbPlace FROM VEHICULE WHERE numMAT = :vehicule");
                queryPlace.bindValue(":vehicule", numMAT);
                if(queryPlace.exec())
                {
                    if(queryPlace.next())
                    {
                        int nombrePlace = queryPlace.value(0).toInt();
                        int placeUtilise = nombrePlace - placeDispo;

                        int row = ui->accueilTableWidget->rowCount();
                        ui->historiqueTableWidget->insertRow(row);
                        ui->historiqueTableWidget->setItem(row, 0, new QTableWidgetItem(numMAT));
                        ui->historiqueTableWidget->setItem(row, 1, new QTableWidgetItem(refTrajet));
                        ui->historiqueTableWidget->setItem(row, 2, new QTableWidgetItem(heure));
                        ui->historiqueTableWidget->setItem(row, 3, new QTableWidgetItem(lieuDepart));
                        ui->historiqueTableWidget->setItem(row, 4, new QTableWidgetItem(destination));
                        ui->historiqueTableWidget->setItem(row, 5, new QTableWidgetItem(dateVoyage.toString()));
                        ui->historiqueTableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(placeUtilise)));
                    }
                }
            }
        }

        int verticalOffset = 0;
        QSqlQuery queryNumMat;
        queryNumMat.prepare("SELECT numMAT, refTrajet FROM VEHICULE");
        if(queryNumMat.exec())
        {
            while(queryNumMat.next())
            {
                int occurence = 0;
                QString numMatriculation = queryNumMat.value(0).toString();
                QString reference = queryNumMat.value(1).toString();
                QSqlQuery queryNbOccurrence;
                queryNbOccurrence.prepare("SELECT dateVoyage FROM GESTION WHERE numMAT = :num");
                queryNbOccurrence.bindValue(":num", numMatriculation);
                if(queryNbOccurrence.exec())
                {
                    while(queryNbOccurrence.next())
                    {
                        QDate date = queryNbOccurrence.value(0).toDate();
                        if(date < QDate::currentDate())
                        {
                            occurence++;
                        }
                    }
                }

                QLabel *numMatLabel = new QLabel("Voiture (" + numMatriculation + "): " + QString::number(occurence) + " voyages effectués (" + reference + ")");
                numMatLabel->setParent(ui->vehiculeContainerHistorique);
                numMatLabel->move(0, verticalOffset);
                verticalOffset += 20;
            }
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }

    ui->membreFamille_2->setItemData(0, QVariant(0), Qt::UserRole - 1);
    ui->refTrajetVehicule->setItemData(0, QVariant(0), Qt::UserRole - 1);
    ui->refTrajet_2->setItemData(0, QVariant(0), Qt::UserRole - 1);
    ui->heureTrajet->setItemData(0, QVariant(0), Qt::UserRole - 1);
    ui->lieuDepart->setItemData(0, QVariant(0), Qt::UserRole - 1);
    ui->lieuArrive->setItemData(0, QVariant(0), Qt::UserRole - 1);

    ui->dateVerify->setDate(QDate::currentDate());
    ui->dateVoyage->setDate(QDate::currentDate());
    ui->dateFiltre->setDate(QDate::currentDate());

    ui->majTrajetBtn->setDisabled(true);
    ui->majVehiculeBtn->setDisabled(true);
    ui->supprTrajetBtn->setDisabled(true);
    ui->supprVehiculeBtn->setDisabled(true);
    ui->refTrajet->setDisabled(true);
    ui->vehicule->setDisabled(true);
    ui->heureReserve->setDisabled(true);
    ui->dateVoyage->setDisabled(true);
    ui->reserver->setDisabled(true);
    ui->majReservationBtn->setDisabled(true);
    ui->supprReservationBtn->setDisabled(true);

    ui->stackedWidget->setCurrentIndex(0);

    QLabel *aproposLabel = new QLabel("\te-Coop est un logiciel capable de gérer les activités d’une entreprise de transport, tel que les coopératives."
                                      "\n\n\tCe logiciel permettra de:\n"
                                      "\n\t\t-Gérer les tours et l’horaire de voyages des véhicules de transport\n"
                                      "\t\t-Ajouter, de modifier ou de supprimer un trajet (itinéraire) ou un véhicule\n"
                                      "\t\t-Mettre à jour les informations de la base de données(BD)\n"
                                      "\t\t-Gérer les réservations des passagers et Stocker tous les historiques des voyages effectués dans la BD\n"
                                      "\n\n\tDéveloppé par :\n"
                                      "\n\t\t--Nantenaina Jérémiah\t\t+261 34 78 668 89\t\tnantenainajeremiah@gmail.com"
                                      "\n\t\t--Ny Aina Haritiana\t\t+261 34 61 716 42\t\tainaramandimby@gmail.com"
                                      "\n\t\t--Tahiry Razanamara\t\t+261 34 55 958 62\t\ttahiryrazanamara01@gmail.com\n\n\n\n\n"
                                      "\n\t\tVersion: 1.0 Beta\t\tDate de création: 9/10/2023\t\tSystème d'exploitation: Windows");
    aproposLabel->setStyleSheet("font-size: 15px;"
                                "font-family: Bahnschrift SemiBold;"
                                "color: rgb(203, 228, 222);");
    aproposLabel->setParent(ui->aproposFrame);

    QString copyrightText = "\t\t\t\t\t\tCopyrights©2023 | Tous droits réservés.";
    QLabel *copyrightLabel = new QLabel(copyrightText);
    copyrightLabel->setStyleSheet("font-size: 13px;"
                                  "font-family: Bahnschrift SemiBold;"
                                  "color: rgb(203, 228, 222);");
    copyrightLabel->setParent(ui->aproposFrame);
    copyrightLabel->move(0, 400);
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

void MainWindow::on_lieuDepart_currentTextChanged(const QString &arg1)
{
    int index = ui->lieuArrive->findText(arg1);
    if(index != -1 && index != 0)
    {
        ui->lieuArrive->setItemData(index, QVariant(index), Qt::UserRole - 1);
        for (int i = 0; i < ui->lieuArrive->count(); ++i)
        {
            if (i != 0 && i != index)
            {
                ui->lieuArrive->setItemData(i, QVariant(true), Qt::UserRole);
            }
        }
    }    
}

void MainWindow::on_lieuArrive_currentTextChanged(const QString &arg1)
{
    int index = ui->lieuDepart->findText(arg1);
    if(index != -1 && index != 0)
    {
        ui->lieuDepart->setItemData(index, QVariant(index), Qt::UserRole - 1);
        for (int i = 0; i < ui->lieuDepart->count(); ++i)
        {
            if (i != 0 && i != index)
            {
                ui->lieuDepart->setItemData(i, QVariant(true), Qt::UserRole);
            }
        }
    }    
}

void MainWindow::on_stackedWidget_currentChanged(int index)
{
    if(index == 0)
    {
        QString style = ui->accueilBtn->styleSheet();
        QString stylesheet = ui->homeIcon->styleSheet();
        style += "background-color: rgb(44, 51, 51);"
                 "border-top-left-radius: 10px;"
                 "border-bottom-left-radius: 10px;"
                 "margin-left: 5px;";
        stylesheet += "background-color: rgb(44, 51, 51);"
                      "border-top-left-radius: 10px;"
                      "border-bottom-left-radius: 10px;"
                      "margin-left: 5px;";
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
        style1 += "background-color: rgb(44, 51, 51);"
                  "border-top-left-radius: 10px;"
                  "border-bottom-left-radius: 10px;"
                  "margin-left: 5px;";
        stylesheet1 += "background-color: rgb(44, 51, 51);"
                       "border-top-left-radius: 10px;"
                       "border-bottom-left-radius: 10px;"
                       "margin-left: 5px;";
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
        style2 += "background-color: rgb(44, 51, 51);"
                  "border-top-left-radius: 10px;"
                  "border-bottom-left-radius: 10px;"
                  "margin-left: 5px;";
        stylesheet2 += "background-color: rgb(44, 51, 51);"
                       "border-top-left-radius: 10px;"
                       "border-bottom-left-radius: 10px;"
                       "margin-left: 5px;";
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
        style3 += "background-color: rgb(44, 51, 51);"
                  "border-top-left-radius: 10px;"
                  "border-bottom-left-radius: 10px;"
                  "margin-left: 5px;";
        stylesheet3 += "background-color: rgb(44, 51, 51);"
                       "border-top-left-radius: 10px;"
                       "border-bottom-left-radius: 10px;"
                       "margin-left: 5px;";
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
        style4 += "background-color: rgb(44, 51, 51);"
                  "border-top-left-radius: 10px;"
                  "border-bottom-left-radius: 10px;"
                  "margin-left: 5px;";
        stylesheet4 += "background-color: rgb(44, 51, 51);"
                       "border-top-left-radius: 10px;"
                       "border-bottom-left-radius: 10px;"
                       "margin-left: 5px;";
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
    msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
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
    msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
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
    QString nomCoop = ui->coopNom->text();
    QString contactCoop = ui->contactCoop->text();
    QString contact1 = ui->contact1->text();
    QString contact2 = ui->contact2->text();
    QString adresseCoop = ui->adresseCoop->text();
    QString datePremierVoyage = ui->datePremierVoyage->text();

    if((!nomCoop.isEmpty()) && (!adresseCoop.isEmpty()) && ((!contactCoop.isEmpty()) || (!contact1.isEmpty()) || (!contact2.isEmpty())))
    {
        Cooperative C;
        if(C.majCoop(nomCoop, contactCoop, contact1, contact2, adresseCoop, datePremierVoyage))
        {
            ui->nomCooperativeParam->setText(nomCoop.toUpper());
            ui->nomCoop->setText(nomCoop.toUpper());
            ui->coopNom->setText(nomCoop.toUpper());

            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
            msgBox.setWindowTitle("");
            msgBox.setText("La coopérative a été mise à jour.");

            msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                 "color: rgb(203, 228, 222);"
                                 "font-size: 13px;");
            msgBox.exec();
            ui->resetCoop->setDisabled(false);
            ui->ajoutTrajetBtn->setDisabled(false);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
            msgBox.setWindowTitle("");
            msgBox.setText("On n'a pas pu mettre à jour la coopérative.");

            msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                 "color: rgb(203, 228, 222);"
                                 "font-size: 13px;");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
        msgBox.setWindowTitle("");
        msgBox.setText("Le nom, l'adresse et au moins un contact télephonique de la coopérative doivent être remplis.");

        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                             "color: rgb(203, 228, 222);"
                             "font-size: 13px;");
        msgBox.exec();
    }
}

void MainWindow::on_pushButton_clicked()
{
    DbManager dbAnnulerCoop(pathToDB);
    if(dbAnnulerCoop.isOpen())
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
            QString datePremierVoyage = query0.value(5).toString();

            ui->coopNom->setText(nomCoop);
            ui->adresseCoop->setText(adresse);
            ui->contactCoop->setText(contact);
            ui->contact1->setText(contact1);
            ui->contact2->setText(contact2);
            ui->datePremierVoyage->setDate(QDate::fromString(datePremierVoyage, "dd/MM/yyyy"));
         }
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}

void MainWindow::on_resetCoop_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
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
        Cooperative C;
        if(C.reinitialiser())
        {
            ui->nomCooperativeParam->setText("");
            ui->nomCoop->setText("");

            ui->coopNom->clear();
            ui->contactCoop->clear();
            ui->contact1->clear();
            ui->contact2->clear();
            ui->adresseCoop->clear();

            ui->refTrajet_2->clear();
            ui->refTrajet_2->addItem("Sélectionner");
            ui->refTrajet_2->setCurrentIndex(0);
            ui->refTrajetVehicule->clear();
            ui->refTrajetVehicule->addItem("Sélectionner");
            ui->refTrajetVehicule->setCurrentIndex(0);
            ui->vehiculeCombobox_2->clear();
            ui->vehiculeCombobox_2->addItem("Tous");
            ui->vehiculeCombobox_2->setCurrentIndex(0);
            ui->heureCombobox_2->clear();
            ui->heureCombobox_2->addItem("Tous");
            ui->heureCombobox_2->setCurrentIndex(0);

            ui->trajetGestionTableView->clearContents();
            ui->trajetGestionTableView->setRowCount(0);
            ui->vehiculeGestionTableView->clearContents();
            ui->vehiculeGestionTableView->setRowCount(0);
            ui->accueilTableWidget->clearContents();
            ui->accueilTableWidget->setRowCount(0);
            ui->historiqueTableWidget->clearContents();
            ui->historiqueTableWidget->setRowCount(0);

            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
            msgBox.setWindowTitle("");
            msgBox.setText("Coopérative réinitialisée, redemarrage de l'application recommandé.");

            msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                 "color: rgb(203, 228, 222);"
                                 "font-size: 13px;");
            msgBox.exec();
            ui->resetCoop->setDisabled(true);
            ui->ajoutTrajetBtn->setDisabled(true);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
            msgBox.setWindowTitle("");
            msgBox.setText("On n'a pas pu réinitialiser la coopérative.");

            msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                 "color: rgb(203, 228, 222);"
                                 "font-size: 13px;");
            msgBox.exec();
        }
    }
}

void MainWindow::on_majVehiculeBtn_clicked()
{
    QString matriculation = ui->matriculation->text();
    QString chauffeur = ui->chauffeur->text();
    QString contact1 = ui->contact_1->text();
    QString refTrajetVehicule = ui->refTrajetVehicule->currentText();
    int nbPlace = ui->placeSupportes->text().toInt();
    int index = ui->refTrajetVehicule->currentIndex();

    if((!chauffeur.isEmpty()) && (!contact1.isEmpty()) && (nbPlace != 0) && (index != 0))
    {
        Vehicule V;
        if(V.modifier_vehicule(matriculation,chauffeur,contact1,nbPlace,refTrajetVehicule))
        {
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

            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
            msgBox.setWindowTitle("");
            msgBox.setText("la voiture a été mise à jour.");

            msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                 "color: rgb(203, 228, 222);"
                                 "font-size: 13px;");
            msgBox.exec();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
            msgBox.setWindowTitle("");
            msgBox.setText("On n'a pas pu mettre à jour le véhicule.");

            msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                 "color: rgb(203, 228, 222);"
                                 "font-size: 13px;");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
        msgBox.setWindowTitle("");
        msgBox.setText("Veuillez remplir toute les cases!\n\nNB: Le nombre de place supporté par le véhicule ne doit pas être égale à 0.");

        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                             "color: rgb(203, 228, 222);"
                             "font-size: 13px;");
        msgBox.exec();
    }
}

void MainWindow::on_ajoutVehiculeBtn_clicked()
{
    QString matriculation = ui->matriculation->text();
    QString chauffeur = ui->chauffeur->text();
    QString contact1 = ui->contact_1->text();
    QString refTrajetVehicule = ui->refTrajetVehicule->currentText();
    int nbPlace = ui->placeSupportes->text().toInt();
    int index = ui->refTrajetVehicule->currentIndex();

    if((!matriculation.isEmpty()) && (!chauffeur.isEmpty()) && (!contact1.isEmpty()) && (nbPlace != 0) && (index != 0))
    {
        Vehicule V;
        if(V.ajouter_vehicule(matriculation,chauffeur,contact1,nbPlace,refTrajetVehicule))
        {
            ui->vehiculeCombobox_2->addItem(matriculation);

            ui->matriculation->clear();
            ui->placeSupportes->setValue(0);
            ui->chauffeur->clear();
            ui->contact_1->clear();
            ui->refTrajetVehicule->setCurrentIndex(0);

            int rowCount = ui->vehiculeGestionTableView->rowCount();
            ui->vehiculeGestionTableView->insertRow(rowCount);

            QTableWidgetItem *itemMatriculation = new QTableWidgetItem(matriculation);
            QTableWidgetItem *itemChauffeur = new QTableWidgetItem(chauffeur.toUpper());
            QTableWidgetItem *itemRefTrajet = new QTableWidgetItem(refTrajetVehicule);
            QTableWidgetItem *itemNbPlace = new QTableWidgetItem(QString::number(nbPlace));

            ui->vehiculeGestionTableView->setItem(rowCount, 0, itemMatriculation);
            ui->vehiculeGestionTableView->setItem(rowCount, 1, itemChauffeur);
            ui->vehiculeGestionTableView->setItem(rowCount, 2, itemNbPlace);
            ui->vehiculeGestionTableView->setItem(rowCount, 3, itemRefTrajet);

            ui->gerer->setDisabled(false);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
            msgBox.setWindowTitle("");
            msgBox.setText("On n'a pas pu ajouter le véhicule.");

            msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                 "color: rgb(203, 228, 222);"
                                 "font-size: 13px;");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
        msgBox.setWindowTitle("");
        msgBox.setText("Veuillez remplir toute les cases!\n\nNB: Le nombre de place supporté par le véhicule ne doit pas être égale à 0.");

        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                             "color: rgb(203, 228, 222);"
                             "font-size: 13px;");
        msgBox.exec();
    }
}

void MainWindow::on_supprVehiculeBtn_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
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

        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
        msgBox.setWindowTitle("");
        msgBox.setText("Véhicule supprimé.");

        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                             "color: rgb(203, 228, 222);"
                             "font-size: 13px;");
        msgBox.exec();
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
    QString lieuDepart = ui->lieuDepart->currentText();
    QString lieuArrive = ui->lieuArrive->currentText();
    QString refTrajet = ui->referenceTrajet->text();
    QString heureMatin = ui->heureMatin_2->text();
    QString heureSoir = ui->heureSoir_2->text();
    int decalage = ui->decalage->text().toInt();

    int index1 = ui->lieuDepart->currentIndex();
    int index2 = ui->lieuArrive->currentIndex();

    if((index1 != 0) && (index2 != 0) && ((heureMatin != heureParDefaut.toString()) || (heureSoir != heureParDefaut.toString())) && (decalage != 0))
    {
        Trajets T;
        if(T.maj_trajet(refTrajet,lieuDepart,lieuArrive,heureMatin,heureSoir,decalage))
        {
            int selectedRow = ui->trajetGestionTableView->currentRow();

            QTableWidgetItem *itemRefTrajet = new QTableWidgetItem(refTrajet);
            QTableWidgetItem *itemLieuDepart = new QTableWidgetItem(lieuDepart);
            QTableWidgetItem *itemLieuArrive = new QTableWidgetItem(lieuArrive);

            ui->trajetGestionTableView->setItem(selectedRow, 0, itemRefTrajet);
            ui->trajetGestionTableView->setItem(selectedRow, 1, itemLieuDepart);
            ui->trajetGestionTableView->setItem(selectedRow, 2, itemLieuArrive);

            ui->trajetGestionTableView->clearSelection();
            ui->trajetGestionTableView->update();

            ui->lieuDepart->setCurrentIndex(0);
            ui->lieuArrive->setCurrentIndex(0);
            ui->heureMatin_2->setTime(heureParDefaut);
            ui->heureSoir_2->setTime(heureParDefaut);
            ui->referenceTrajet->clear();

            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
            msgBox.setWindowTitle("");
            msgBox.setText("Le trajet a été mis à jour.");

            msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                 "color: rgb(203, 228, 222);"
                                 "font-size: 13px;");
            msgBox.exec();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
            msgBox.setWindowTitle("");
            msgBox.setText("On n'a pas pu mettre à jour le trajet.");

            msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                 "color: rgb(203, 228, 222);"
                                 "font-size: 13px;");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
        msgBox.setWindowTitle("");
        msgBox.setText("Veuillez remplir toute les cases!\n\nNB: L'heure ne doit pas être '00:00', et le décalage des voyages ne doit pas être égale à 0.");

        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                             "color: rgb(203, 228, 222);"
                             "font-size: 13px;");
        msgBox.exec();
    }
}

void MainWindow::on_ajoutTrajetBtn_clicked()
{
    QTime heureParDefaut(0, 0);
    QString lieuDepart = ui->lieuDepart->currentText();
    QString lieuArrive = ui->lieuArrive->currentText();
    QString refTrajet = ui->referenceTrajet->text();
    QString heureMatin = ui->heureMatin_2->text();
    QString heureSoir = ui->heureSoir_2->text();
    int decalage = ui->decalage->text().toInt();

    int index1 = ui->lieuDepart->currentIndex();
    int index2 = ui->lieuArrive->currentIndex();

    if((index1 != 0) && (index2 != 0) && ((heureMatin != heureParDefaut.toString()) || (heureSoir != heureParDefaut.toString())) && (!refTrajet.isEmpty()) && (decalage != 0))
    {
        if(index1 == index2)
        {
            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
            msgBox.setWindowTitle("");
            msgBox.setText("Vous ne pouvez pas entrer le même lieu de départ et de destination.");

            msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                 "color: rgb(203, 228, 222);"
                                 "font-size: 13px;");
            msgBox.exec();
        }
        else
        {
            Trajets T;
            if(T.ajout_trajet(refTrajet,lieuDepart,lieuArrive,heureMatin,heureSoir,decalage))
            {
                ui->refTrajetVehicule->addItem(refTrajet);
                ui->refTrajet_2->addItem(refTrajet);
                ui->heureCombobox_2->addItem(heureSoir);
                ui->heureCombobox_2->addItem(heureMatin);

                int rowCount = ui->trajetGestionTableView->rowCount();
                ui->trajetGestionTableView->insertRow(rowCount);

                QTableWidgetItem *itemRefTrajet = new QTableWidgetItem(refTrajet);
                QTableWidgetItem *itemLieuDepart = new QTableWidgetItem(lieuDepart);
                QTableWidgetItem *itemLieuArrive = new QTableWidgetItem(lieuArrive);

                ui->trajetGestionTableView->setItem(rowCount, 0, itemRefTrajet);
                ui->trajetGestionTableView->setItem(rowCount, 1, itemLieuDepart);
                ui->trajetGestionTableView->setItem(rowCount, 2, itemLieuArrive);

                ui->lieuDepart->setCurrentIndex(0);
                ui->lieuArrive->setCurrentIndex(0);
                ui->heureMatin_2->setTime(heureParDefaut);
                ui->heureSoir_2->setTime(heureParDefaut);
                ui->referenceTrajet->clear();
                ui->decalage->setValue(0);

                ui->ajoutVehiculeBtn->setDisabled(false);
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
                msgBox.setWindowTitle("");
                msgBox.setText("On n'a pas pu ajouter le trajet.");

                msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                     "color: rgb(203, 228, 222);"
                                     "font-size: 13px;");
                msgBox.exec();
             }
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
        msgBox.setWindowTitle("");
        msgBox.setText("Veuillez remplir toute les cases!\n\nNB: L'heure ne doit pas être '00:00', et le décalage des voyages ne doit pas être égale à 0.");

        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                             "color: rgb(203, 228, 222);"
                             "font-size: 13px;");
        msgBox.exec();
    }
}

void MainWindow::on_supprTrajetBtn_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
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
        QTime heureParDefaut(0, 0);
        QString refTrajet = ui->referenceTrajet->text();

        DbManager dbSupprVehicule(pathToDB);
        if(dbSupprVehicule.isOpen())
        {
            QSqlQuery query;
            query.prepare("DELETE FROM VEHICULE WHERE refTrajet = :refTrajet");
            query.bindValue(":refTrajet", refTrajet);

            Trajets T;
            if((query.exec()) && (T.supprimer_trajet(refTrajet)))
            {
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
                int numRowDeleted = 0;

                for(int i = 0; i < rowCount; ++i)
                {
                    QTableWidgetItem *item = ui->vehiculeGestionTableView->item(i - numRowDeleted, columnIndex);
                    if(item && item->text() == refTrajet)
                    {
                        ui->vehiculeGestionTableView->removeRow(i - numRowDeleted);
                        numRowDeleted++;
                    }
                }

                ui->vehiculeGestionTableView->update();

                ui->lieuDepart->setCurrentIndex(0);
                ui->lieuArrive->setCurrentIndex(0);
                ui->heureMatin_2->setTime(heureParDefaut);
                ui->heureSoir_2->setTime(heureParDefaut);
                ui->referenceTrajet->clear();

                QMessageBox msgBox;
                msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
                msgBox.setWindowTitle("");
                msgBox.setText("Trajet supprimé.");

                msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                     "color: rgb(203, 228, 222);"
                                     "font-size: 13px;");
                msgBox.exec();
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
                msgBox.setWindowTitle("");
                msgBox.setText("On n'a pas pu supprimer le trajet.");
                msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                     "color: rgb(203, 228, 222);"
                                     "font-size: 13px;");
                msgBox.exec();
            }
        }
    }
}

void MainWindow::on_annulerTrajetBtn_clicked()
{
    QTime heureParDefaut(0, 0);
    ui->trajetGestionTableView->clearSelection();
    ui->lieuDepart->setCurrentIndex(0);
    ui->lieuArrive->setCurrentIndex(0);
    ui->heureMatin_2->setTime(heureParDefaut);
    ui->heureSoir_2->setTime(heureParDefaut);
    ui->referenceTrajet->clear();
    ui->decalage->setValue(0);
    ui->refTrajetVehicule->setCurrentIndex(0);
}

void MainWindow::on_reserver_clicked()
{
    QString nomPass = ui->nomInput_2->text();
    QString contactPass = ui->contactInput_2->text();
    QString cin = ui->cin_2->text();
    QString refPlace = ui->referencePlace->text();
    QString membreFamille = ui->membreFamille_2->currentText();
    QString contactFamille = ui->contactFamille_2->text();
    QString voiture = ui->vehicule->text();
    QString refTrajet = ui->refTrajet->text();
    QDate dateVoyage = ui->dateVoyage->date();
    QString heureDepart = ui->heureReserve->text();
    int nbPlace = ui->nombrePlace_2->value();
    int indexFamille = ui->membreFamille_2->currentIndex();

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

    if((!nomPass.isEmpty()) && (!contactPass.isEmpty()) && (!cin.isEmpty()) && (!refPlace.isEmpty()) && (indexFamille != 0) && (!contactFamille.isEmpty()) && (nbPlace != 0))
    {
        DbManager dbReserver(pathToDB);
        if(dbReserver.isOpen())
        {
            QSqlQuery queryReserver;
            queryReserver.prepare("SELECT placeDispo, lieuDepart, destination FROM GESTION WHERE numMAT = :numMat AND refTrajet = :refTrajet AND dateVoyage = :date");
            queryReserver.bindValue(":numMat", voiture);
            queryReserver.bindValue(":refTrajet", refTrajet);
            queryReserver.bindValue(":date", dateVoyage);

            if(queryReserver.exec())
            {
                if(queryReserver.next())
                {
                    int placeDispo = queryReserver.value(0).toInt();
                    QString depart = queryReserver.value(1).toString();
                    QString dest = queryReserver.value(2).toString();

                    if(placeDispo >= nbPlace)
                    {
                        placeDispo = placeDispo - nbPlace;

                        QSqlQuery place;
                        place.prepare("UPDATE GESTION SET placeDispo = :place WHERE numMAT = :numMat AND refTrajet = :refTrajet AND dateVoyage = :date");
                        place.bindValue(":place", placeDispo);
                        place.bindValue(":numMat", voiture);
                        place.bindValue(":refTrajet", refTrajet);
                        place.bindValue(":date", dateVoyage);

                        if(place.exec())
                        {
                            Reservation R;
                            if(R.reserver(refPlace, nomPass, contactPass, cin, nbPlace, membreFamille,contactFamille, voiture, refTrajet, dateVoyage.toString("yyyy-MM-dd"), heureDepart, isPaye, depart, dest))
                            {
                                ui->reservationTableView->clearContents();
                                ui->reservationTableView->setRowCount(0);

                                DbManager dbPassager(pathToDB);
                                if(dbPassager.isOpen())
                                {
                                    QSqlQuery affichagePassager;
                                    affichagePassager.prepare("SELECT nomPass, nbPlaceReserve, isPaye, contactPass, Id, refPlace FROM PASSAGER"
                                                              " WHERE refTrajet = :ref AND dateVoyage = :date AND heureDepart = :heure");
                                    affichagePassager.bindValue(":ref", refTrajet);
                                    affichagePassager.bindValue(":date", dateVoyage.toString("yyyy-MM-dd"));
                                    affichagePassager.bindValue(":heure", heureDepart);

                                    if(affichagePassager.exec())
                                    {
                                        while(affichagePassager.next())
                                        {
                                            QString nomPass = affichagePassager.value(0).toString();
                                            int nbPlaceReserve = affichagePassager.value(1).toInt();
                                            bool isPaye = affichagePassager.value(2).toBool();
                                            QString contactPass = affichagePassager.value(3).toString();
                                            int id = affichagePassager.value(4).toInt();
                                            QString referencePlace = affichagePassager.value(5).toString();

                                            int row = ui->reservationTableView->rowCount();
                                            ui->reservationTableView->insertRow(row);
                                            ui->reservationTableView->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
                                            ui->reservationTableView->setItem(row, 1, new QTableWidgetItem(referencePlace));
                                            ui->reservationTableView->setItem(row, 2, new QTableWidgetItem(nomPass));
                                            ui->reservationTableView->setItem(row, 3, new QTableWidgetItem(QString::number(nbPlaceReserve)));
                                            ui->reservationTableView->setItem(row, 4, new QTableWidgetItem(isPaye ? "Payé" : "Non Payé"));
                                            ui->reservationTableView->setItem(row, 5, new QTableWidgetItem(contactPass));
                                        }
                                    }
                                    else
                                    {
                                        qDebug() << "-----Erreur: " << affichagePassager.lastError().text();
                                    }
                                }

                                for(int row = 0; row < ui->trajetReservationTableView->rowCount(); row++)
                                {
                                    QTableWidgetItem *item = ui->trajetReservationTableView->item(row, 0);
                                    if(item && item->text() == voiture)
                                    {
                                        QTableWidgetItem *placeDisponible = new QTableWidgetItem(QString::number(placeDispo));
                                        ui->trajetReservationTableView->setItem(row, 3, placeDisponible);
                                        break;
                                    }
                                }

                                QMessageBox msgBox;
                                msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
                                msgBox.setWindowTitle("");
                                msgBox.setText("Passager(s) réservé(s) avec succès.");
                                msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                                     "color: rgb(203, 228, 222);"
                                                     "font-size: 13px;");
                                msgBox.exec();

                                ui->nomInput_2->clear();
                                ui->contactInput_2->clear();
                                ui->cin_2->clear();
                                ui->referencePlace->clear();
                                ui->membreFamille_2->setCurrentIndex(0);
                                ui->contactFamille_2->clear();
                                ui->nombrePlace_2->setValue(0);
                                ui->frais_2->setCurrentIndex(0);
                            }
                        }
                        else
                        {
                            QMessageBox msgBox;
                            msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
                            msgBox.setWindowTitle("");
                            msgBox.setText("Echec de reservation");
                            msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                                 "color: rgb(203, 228, 222);"
                                                 "font-size: 13px;");
                            msgBox.exec();
                        }
                    }
                    else
                    {
                        QMessageBox msgBox;
                        msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
                        msgBox.setWindowTitle("");
                        msgBox.setText("Le nombre des places disponibles est insuffisant!");
                        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                             "color: rgb(203, 228, 222);"
                                             "font-size: 13px;");
                        msgBox.exec();
                    }
                }
                else
                {
                    QMessageBox msgBox;
                    msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
                    msgBox.setWindowTitle("");
                    msgBox.setText("Réservation échoué!");
                    msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                         "color: rgb(203, 228, 222);"
                                         "font-size: 13px;");
                    msgBox.exec();
                }
            }
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
        msgBox.setWindowTitle("");
        msgBox.setText("Veuillez remplir toute les cases!");
        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                             "color: rgb(203, 228, 222);"
                             "font-size: 13px;");
        msgBox.exec();
    }
}

void MainWindow::on_majReservationBtn_clicked()
{
    QString nomPass = ui->nomInput_2->text();
    QString contactPass = ui->contactInput_2->text();
    QString cin = ui->cin_2->text();
    QString refPlace = ui->referencePlace->text();
    QString membreFamille = ui->membreFamille_2->currentText();
    QString contactFamille = ui->contactFamille_2->text();
    QString voiture = ui->vehicule->text();
    QString refTrajet = ui->refTrajet->text();
    QDate dateVoyage = ui->dateVoyage->date();
    int nbPlace = ui->nombrePlace_2->value();
    int indexPaye = ui->frais_2->currentIndex();
    int indexFamille = ui->membreFamille_2->currentIndex();
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

    if((!nomPass.isEmpty()) && (!contactPass.isEmpty()) && (!cin.isEmpty()) && (!refPlace.isEmpty()) && (indexFamille != 0) && (!contactFamille.isEmpty()) && (nbPlace != 0))
    {
        QItemSelectionModel *selectionModel = ui->reservationTableView->selectionModel();
        QModelIndexList selectedIndex = selectionModel->selectedRows();

        if(!selectedIndex.isEmpty())
        {
            QModelIndex id = selectedIndex.first().sibling(selectedIndex.first().row(), 0);
            QVariant idData = ui->reservationTableView->model()->data(id);

            if(idData.isValid())
            {
                DbManager dbMaj(pathToDB);
                if(dbMaj.isOpen())
                {
                    QSqlQuery query;
                    query.prepare("SELECT placeDispo FROM GESTION WHERE numMAT = :numMat AND refTrajet = :refTrajet AND dateVoyage = :date");
                    query.bindValue(":numMat", voiture);
                    query.bindValue(":refTrajet", refTrajet);
                    query.bindValue(":date", dateVoyage);
                    if(query.exec())
                    {
                        if(query.next())
                        {
                            int placeDispoAvant = query.value(0).toInt();
                            if(placeDispoAvant >= nbPlace)
                            {
                                int _id = idData.toInt();
                                QSqlQuery query1;
                                query1.prepare("SELECT nbPlaceReserve FROM PASSAGER WHERE Id = :Id");
                                query1.bindValue(":Id", _id);

                                Reservation R;
                                if((query1.exec()) && (R.majReservation(_id, refPlace, nomPass, contactPass, cin, nbPlace, membreFamille, contactFamille, isPaye)))
                                {
                                    if(query1.next())
                                    {
                                        int nbPlaceReserve = query1.value(0).toInt();
                                        int diffPlace = nbPlaceReserve - nbPlace;
                                        int placeDispoApres = placeDispoAvant + diffPlace;

                                        DbManager dbNbPlace(pathToDB);
                                        if(dbNbPlace.isOpen())
                                        {
                                            QSqlQuery place;
                                            place.prepare("UPDATE GESTION SET placeDispo = :place WHERE numMAT = :numMat AND refTrajet = :refTrajet AND dateVoyage = :date");
                                            place.bindValue(":place", placeDispoApres);
                                            place.bindValue(":numMat", voiture);
                                            place.bindValue(":refTrajet", refTrajet);
                                            place.bindValue(":date", dateVoyage);
                                            if(place.exec())
                                            {
                                                qDebug() << "Updated.";
                                            }
                                            else
                                            {
                                                qDebug() << "Update failed.";
                                            }
                                        }

                                        for(int row = 0; row < ui->trajetReservationTableView->rowCount(); row++)
                                        {
                                            QTableWidgetItem *item = ui->trajetReservationTableView->item(row, 0);
                                            if(item && item->text() == voiture)
                                            {
                                                QTableWidgetItem *placeDisponible = new QTableWidgetItem(QString::number(placeDispoApres));
                                                ui->trajetReservationTableView->setItem(row, 3, placeDisponible);
                                                break;
                                            }
                                        }

                                        int selectedRow = ui->reservationTableView->currentRow();
                                        ui->reservationTableView->setItem(selectedRow, 0, new QTableWidgetItem(QString::number(_id)));
                                        ui->reservationTableView->setItem(selectedRow, 1, new QTableWidgetItem(refPlace));
                                        ui->reservationTableView->setItem(selectedRow, 2, new QTableWidgetItem(nomPass));
                                        ui->reservationTableView->setItem(selectedRow, 3, new QTableWidgetItem(QString::number(nbPlace)));
                                        ui->reservationTableView->setItem(selectedRow, 4, new QTableWidgetItem(isPaye ? "Payé" : "Non payé"));
                                        ui->reservationTableView->setItem(selectedRow, 5, new QTableWidgetItem(contactPass));

                                        ui->reservationTableView->clearSelection();
                                        ui->reservationTableView->update();

                                        ui->majReservationBtn->setDisabled(true);
                                        ui->supprReservationBtn->setDisabled(true);
                                        ui->reserver->setEnabled(true);

                                        QMessageBox msgBox;
                                        msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
                                        msgBox.setWindowTitle("");
                                        msgBox.setText("Passager est à jour avec succès.");
                                        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                                             "color: rgb(203, 228, 222);"
                                                             "font-size: 13px;");
                                        msgBox.exec();

                                        ui->nomInput_2->clear();
                                        ui->contactInput_2->clear();
                                        ui->cin_2->clear();
                                        ui->referencePlace->clear();
                                        ui->membreFamille_2->setCurrentIndex(0);
                                        ui->contactFamille_2->clear();
                                        ui->nombrePlace_2->setValue(0);
                                        ui->frais_2->setCurrentIndex(0);
                                    }
                                }
                            }
                            else
                            {
                                QMessageBox msgBox;
                                msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
                                msgBox.setWindowTitle("");
                                msgBox.setText("Le nombre des places disponibles est insuffisant!");
                                msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                                     "color: rgb(203, 228, 222);"
                                                     "font-size: 13px;");
                                msgBox.exec();
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
        msgBox.setWindowTitle("");
        msgBox.setText("Veuillez remplir toute les cases!");
        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                             "color: rgb(203, 228, 222);"
                             "font-size: 13px;");
        msgBox.exec();
    }
}

void MainWindow::on_supprReservationBtn_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
    msgBox.setWindowTitle("Confirmation de suppression");
    msgBox.setText("Êtes-vous sûr de vouloir supprimer ce(s) passager(s)?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                         "color: rgb(203, 228, 222);"
                         "font-size: 13px;");

    msgBox.setButtonText(QMessageBox::Yes, "Oui");
    msgBox.setButtonText(QMessageBox::No, "Non");

    if (msgBox.exec() == QMessageBox::Yes)
    {
        QItemSelectionModel *selectionModel = ui->reservationTableView->selectionModel();
        QModelIndexList selectedIndex = selectionModel->selectedRows();
        if(!selectedIndex.isEmpty())
        {
            QModelIndex id = selectedIndex.first().sibling(selectedIndex.first().row(), 0);
            QVariant idData = ui->reservationTableView->model()->data(id);

            if(idData.isValid())
            {
                int _id = idData.toInt();

                DbManager dbReserver(pathToDB);
                if(dbReserver.isOpen())
                {
                    QSqlQuery query;
                    query.prepare("SELECT voiture, refTrajet, dateVoyage, nbPlaceReserve FROM PASSAGER WHERE Id = :Id");
                    query.bindValue(":Id", _id);

                    if(query.exec())
                    {
                        if(query.next())
                        {
                            QString voiture = query.value(0).toString();
                            QString refTrajet = query.value(1).toString();
                            QString dateVoyage = query.value(2).toString();
                            int nbPlace = query.value(3).toInt();

                            QSqlQuery queryplace;
                            queryplace.prepare("SELECT placeDispo FROM GESTION WHERE numMAT = :numMat AND refTrajet = :refTrajet AND dateVoyage = :date");
                            queryplace.bindValue(":numMat", voiture);
                            queryplace.bindValue(":refTrajet", refTrajet);
                            queryplace.bindValue(":date", dateVoyage);

                            if(queryplace.exec())
                            {
                                if(queryplace.next())
                                {
                                    int placeDispo = queryplace.value(0).toInt();
                                    placeDispo = placeDispo + nbPlace;

                                    QSqlQuery place;
                                    place.prepare("UPDATE GESTION SET placeDispo = :place WHERE numMAT = :numMat AND refTrajet = :refTrajet AND dateVoyage = :date");
                                    place.bindValue(":place", placeDispo);
                                    place.bindValue(":numMat", voiture);
                                    place.bindValue(":refTrajet", refTrajet);
                                    place.bindValue(":date", dateVoyage);

                                    Reservation R;
                                    if((place.exec()) && (R.supprReservation(_id)))
                                    {
                                        for(int row = 0; row < ui->trajetReservationTableView->rowCount(); row++)
                                        {
                                            QTableWidgetItem *item = ui->trajetReservationTableView->item(row, 0);
                                            if(item && item->text() == voiture)
                                            {
                                                QTableWidgetItem *placeDisponible = new QTableWidgetItem(QString::number(placeDispo));
                                                ui->trajetReservationTableView->setItem(row, 3, placeDisponible);
                                                break;
                                            }
                                        }
                                        int selectedRow = ui->reservationTableView->currentRow();
                                        ui->reservationTableView->removeRow(selectedRow);
                                        ui->reservationTableView->update();

                                        ui->majReservationBtn->setDisabled(true);
                                        ui->supprReservationBtn->setDisabled(true);
                                        ui->reserver->setEnabled(true);
                                        QMessageBox msgBox;
                                        msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
                                        msgBox.setWindowTitle("");
                                        msgBox.setText("Passager(s) supprimé(s).");
                                        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                                             "color: rgb(203, 228, 222);"
                                                             "font-size: 13px;");
                                        msgBox.exec();

                                        ui->nomInput_2->clear();
                                        ui->contactInput_2->clear();
                                        ui->cin_2->clear();
                                        ui->referencePlace->clear();
                                        ui->membreFamille_2->setCurrentIndex(0);
                                        ui->contactFamille_2->clear();
                                        ui->nombrePlace_2->setValue(0);
                                        ui->frais_2->setCurrentIndex(0);
                                    }
                                    else
                                    {
                                        QMessageBox msgBox;
                                        msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
                                        msgBox.setWindowTitle("");
                                        msgBox.setText("On n'a pas pu supprimer le(s) passager(s).");
                                        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                                             "color: rgb(203, 228, 222);"
                                                             "font-size: 13px;");
                                        msgBox.exec();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::on_annulerReserve_clicked()
{
    ui->nomInput_2->clear();
    ui->contactInput_2->clear();
    ui->cin_2->clear();
    ui->referencePlace->clear();
    ui->membreFamille_2->setCurrentIndex(0);
    ui->contactFamille_2->clear();
    ui->nombrePlace_2->setValue(0);
    ui->frais_2->setCurrentIndex(0);
    ui->reservationTableView->clearSelection();
    ui->majReservationBtn->setDisabled(true);
    ui->supprReservationBtn->setDisabled(true);
    ui->reserver->setDisabled(false);
}

void MainWindow::on_annulerVerifBtn_clicked()
{
    ui->refTrajet_2->setCurrentIndex(0);
    ui->dateVerify->setDate(QDate::currentDate());
    ui->heureTrajet->setCurrentIndex(0);
    ui->trajetReservationTableView->clearContents();
    ui->trajetReservationTableView->setRowCount(0);
    ui->vehicule->clear();
    ui->refTrajet->clear();
    ui->heureReserve->clear();
    ui->dateVoyage->setDate(QDate::currentDate());
    ui->reservationTableView->clearContents();
    ui->reservationTableView->setRowCount(0);
    ui->reserver->setDisabled(true);
    ui->frais_2->setCurrentIndex(0);
}

void MainWindow::on_parDefaut_clicked()
{
    ui->vehiculeCombobox_2->setCurrentIndex(0);
    ui->dateFiltre->setDate(QDate::currentDate());
    ui->heureCombobox_2->setCurrentIndex(0);
    ui->historiqueTableWidget->clearSelection();
}

void MainWindow::on_gerer_clicked()
{
    DbManager dbGerer(pathToDB);
    if(dbGerer.isOpen())
    {
        QSqlQuery query0;
        query0.prepare("SELECT * FROM TRAJET");
        QSqlQuery query1;
        query1.prepare("SELECT * FROM VEHICULE");

        if((query0.exec()) && (query1.exec()))
        {
            if((query0.next()) && (query1.next()))
            {
                QSqlQuery query;
                query.prepare("DELETE FROM GESTION");
                if(query.exec())
                {
                    ui->accueilTableWidget->clearContents();
                    ui->accueilTableWidget->setRowCount(0);
                    gestionTrajet g;
                    if(g.gerer())
                    {
                        DbManager dbAccueil(pathToDB);
                        if(dbAccueil.isOpen())
                        {
                            QSqlQuery query;
                            query.exec("SELECT numMAT, refTrajet, heure, lieuDepart, destination, dateVoyage, placeDispo FROM GESTION");
                            while(query.next())
                            {
                                QString numMAT = query.value(0).toString();
                                QString refTrajet = query.value(1).toString();
                                QString heure = query.value(2).toString();
                                QString lieuDepart = query.value(3).toString();
                                QString destination = query.value(4).toString();
                                QDate dateVoyage = query.value(5).toDate();
                                int placeDispo = query.value(6).toInt();

                                if((dateVoyage >= QDate::currentDate()) && (dateVoyage <= QDate::currentDate().addDays(7)))
                                {
                                    int row = ui->accueilTableWidget->rowCount();

                                    ui->accueilTableWidget->insertRow(row);
                                    ui->accueilTableWidget->setItem(row, 0, new QTableWidgetItem(numMAT));
                                    ui->accueilTableWidget->setItem(row, 1, new QTableWidgetItem(refTrajet));
                                    ui->accueilTableWidget->setItem(row, 2, new QTableWidgetItem(heure));
                                    ui->accueilTableWidget->setItem(row, 3, new QTableWidgetItem(lieuDepart));
                                    ui->accueilTableWidget->setItem(row, 4, new QTableWidgetItem(destination));
                                    ui->accueilTableWidget->setItem(row, 5, new QTableWidgetItem(dateVoyage.toString()));
                                    ui->accueilTableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(placeDispo)));
                                }
                            }
                        }
                        QMessageBox msgBox;
                        msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
                        msgBox.setWindowTitle("");
                        msgBox.setText("Les trajets sont gerés avec succès!");
                        msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                             "color: rgb(203, 228, 222);"
                                             "font-size: 13px;");
                        msgBox.exec();
                    }
                }
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
                msgBox.setWindowTitle("");
                msgBox.setText("On n'a pas pu gérer les trajets!");
                msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                     "color: rgb(203, 228, 222);"
                                     "font-size: 13px;");
                msgBox.exec();
            }
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }
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
        queryVerify.prepare("SELECT numMAT, lieuDepart, destination, placeDispo FROM GESTION WHERE refTrajet = :refTrajet AND dateVoyage = :date AND heure = :heure");
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
                int placeDispo = queryVerify.value(3).toInt();

                int row = ui->trajetReservationTableView->rowCount();

                ui->trajetReservationTableView->insertRow(row);
                ui->trajetReservationTableView->setItem(row, 0, new QTableWidgetItem(numMAT));
                ui->trajetReservationTableView->setItem(row, 1, new QTableWidgetItem(lieuDepart));
                ui->trajetReservationTableView->setItem(row, 2, new QTableWidgetItem(destination));
                ui->trajetReservationTableView->setItem(row, 3, new QTableWidgetItem(QString::number(placeDispo)));
            }

            if(ui->trajetReservationTableView->rowCount() == 0)
            {
                QMessageBox msgBox;
                msgBox.setWindowIcon(QIcon(":/Icons/Bold Icons/logoecoop.svg"));
                msgBox.setWindowTitle("");
                msgBox.setText("Aucun voyage recommandé.");
                msgBox.setStyleSheet("background-color: rgb(44, 51, 51);"
                                     "color: rgb(203, 228, 222);"
                                     "font-size: 13px;");
                msgBox.exec();
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
                    ui->lieuDepart->setCurrentText(lieuDepart);
                    ui->lieuArrive->setCurrentText(destination);
                    ui->heureMatin_2->setTime(heureMatin1);
                    ui->heureSoir_2->setTime(heureSoir1);
                    ui->decalage->setValue(decalage);
                    ui->refTrajetVehicule->setCurrentText(refTrajet);
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
    ui->reservationTableView->clearContents();
    ui->reservationTableView->setRowCount(0);

    if(itemNumMat)
    {
        DbManager db4(pathToDB);
        if(db4.isOpen())
        {
            QString numMat = itemNumMat->text();
            QString heure_depart = ui->heureTrajet->currentText();
            QDate dateVoyage = ui->dateVerify->date();

            QSqlQuery queryReserve;

            queryReserve.prepare("SELECT refTrajet FROM GESTION WHERE numMAT = :numMat AND heure = :heure AND dateVoyage = :date");
            queryReserve.bindValue(":numMat", numMat);
            queryReserve.bindValue(":heure", heure_depart);
            queryReserve.bindValue(":date", dateVoyage);

            if(queryReserve.exec())
            {
                while(queryReserve.next())
                {
                    QString refTrajet = queryReserve.value(0).toString();

                    ui->vehicule->setText(numMat);
                    ui->refTrajet->setText(refTrajet);
                    ui->heureReserve->setText(heure_depart);
                    ui->dateVoyage->setDate(dateVoyage);
                    ui->reserver->setDisabled(false);

                    QSqlQuery affichagePassager;
                    affichagePassager.prepare("SELECT refPlace, nomPass, nbPlaceReserve, isPaye, contactPass, Id FROM PASSAGER"
                                              " WHERE refTrajet = :ref AND dateVoyage = :date AND heureDepart = :heure AND voiture = :num");
                    affichagePassager.bindValue(":ref", refTrajet);
                    affichagePassager.bindValue(":date", dateVoyage.toString("yyyy-MM-dd"));
                    affichagePassager.bindValue(":heure", heure_depart);
                    affichagePassager.bindValue(":num", numMat);

                    if(affichagePassager.exec())
                    {
                        while(affichagePassager.next())
                        {
                            QString refPlace = affichagePassager.value(0).toString();
                            QString nomPass = affichagePassager.value(1).toString();
                            int nbPlaceReserve = affichagePassager.value(2).toInt();
                            bool isPaye = affichagePassager.value(3).toBool();
                            QString contactPass = affichagePassager.value(4).toString();
                            int id = affichagePassager.value(5).toInt();

                            int row = ui->reservationTableView->rowCount();
                            ui->reservationTableView->insertRow(row);
                            ui->reservationTableView->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
                            ui->reservationTableView->setItem(row, 1, new QTableWidgetItem(refPlace));
                            ui->reservationTableView->setItem(row, 2, new QTableWidgetItem(nomPass));
                            ui->reservationTableView->setItem(row, 3, new QTableWidgetItem(QString::number(nbPlaceReserve)));
                            ui->reservationTableView->setItem(row, 4, new QTableWidgetItem(isPaye ? "Payé" : "Non Payé"));
                            ui->reservationTableView->setItem(row, 5, new QTableWidgetItem(contactPass));
                        }
                    }
                }
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
        ui->lieuDepart->setCurrentIndex(0);
        ui->lieuArrive->setCurrentIndex(0);
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


void MainWindow::on_reservationTableView_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();
    QTableWidgetItem* itemId = ui->reservationTableView->item(row, 0);
    QTableWidgetItem* itemRefPlace = ui->reservationTableView->item(row, 1);
    QTableWidgetItem* itemNom = ui->reservationTableView->item(row, 2);
    QTableWidgetItem* itemNbPlace = ui->reservationTableView->item(row, 3);
    QTableWidgetItem* itemFrais = ui->reservationTableView->item(row, 4);
    QTableWidgetItem* itemContact = ui->reservationTableView->item(row, 5);

    if(itemRefPlace && itemNom && itemNbPlace && itemFrais && itemContact)
    {
        ui->majReservationBtn->setDisabled(false);
        ui->reserver->setDisabled(true);

        DbManager db3(pathToDB);
        if(db3.isOpen())
        {
            int id = itemId->text().toInt();
            QString refPlace = itemRefPlace->text();
            QString nom = itemNom->text();
            int nbPlace = itemNbPlace->text().toInt();
            QString frais = itemFrais->text();
            QString contact = itemContact->text();

            QSqlQuery queryAffichageReservation;

            queryAffichageReservation.prepare("SELECT membreFamille, contactFamille, refTrajet, heureDepart, lieuDepart, destination, dateVoyage, voiture, cin FROM PASSAGER "
                                              "WHERE Id = :id");
            queryAffichageReservation.bindValue(":id", id);
            if(queryAffichageReservation.exec())
            {
                while(queryAffichageReservation.next())
                {
                    QString membreFamille = queryAffichageReservation.value(0).toString();
                    QString contactFamille = queryAffichageReservation.value(1).toString();
                    QString refTrajet = queryAffichageReservation.value(2).toString();
                    QString heureDepart = queryAffichageReservation.value(3).toString();
                    QString lieuDepart = queryAffichageReservation.value(4).toString();
                    QString destination = queryAffichageReservation.value(5).toString();
                    QDate dateVoyage = queryAffichageReservation.value(6).toDate();
                    QString voiture = queryAffichageReservation.value(7).toString();
                    QString cin = queryAffichageReservation.value(8).toString();

                    ui->nomInput_2->setText(nom);
                    ui->contactInput_2->setText(contact);
                    ui->cin_2->setText(cin);
                    ui->referencePlace->setText(refPlace);
                    ui->membreFamille_2->setCurrentText(membreFamille);
                    ui->contactFamille_2->setText(contactFamille);
                    ui->refTrajet->setText(refTrajet);
                    ui->vehicule->setText(voiture);
                    ui->dateVoyage->setDate(dateVoyage);
                    ui->heureReserve->setText(heureDepart);
                    ui->nombrePlace_2->setValue(nbPlace);
                    if(frais == "Payé")
                    {
                        ui->frais_2->setCurrentIndex(1);
                        ui->supprReservationBtn->setDisabled(true);
                    }
                    else if(frais == "Non Payé")
                    {
                        ui->frais_2->setCurrentIndex(0);
                        ui->supprReservationBtn->setDisabled(false);
                    }
                }
            }
            else
            {
                qDebug() << "Query error:" << queryAffichageReservation.lastError().text();
            }
        }
        else
        {
            qDebug() << "Database not opened.";
        }
    }
}

void MainWindow::on_vehiculeCombobox_2_currentTextChanged(const QString &arg1)
{
    for(int row = 0; row < ui->historiqueTableWidget->rowCount(); ++row)
    {
        QTableWidgetItem *item = ui->historiqueTableWidget->item(row, 0);
        if(item)
        {
            QString cellText = item->text();
            if(cellText == arg1)
            {
                ui->historiqueTableWidget->showRow(row);
            }
            else
            {
                ui->historiqueTableWidget->hideRow(row);
            }
        }
        if(arg1 == "Tous")
        {
            ui->historiqueTableWidget->showRow(row);
        }
    }
}

void MainWindow::on_heureCombobox_2_currentTextChanged(const QString &arg1)
{
    for(int row = 0; row < ui->historiqueTableWidget->rowCount(); ++row)
    {
        QTableWidgetItem *item = ui->historiqueTableWidget->item(row, 2);
        if(item)
        {
            QString cellText = item->text();
            if(cellText == arg1)
            {
                ui->historiqueTableWidget->showRow(row);
            }
            else
            {
                ui->historiqueTableWidget->hideRow(row);
            }
        }
        if(arg1 == "Tous")
        {
            ui->historiqueTableWidget->showRow(row);
        }
    }
}

void MainWindow::on_dateFiltre_dateChanged(const QDate &date)
{
    for(int row = 0; row < ui->historiqueTableWidget->rowCount(); ++row)
    {
        QTableWidgetItem *item = ui->historiqueTableWidget->item(row, 5);
        if(item)
        {
            QDate cellDate = QDate::fromString(item->text(), Qt::TextDate);
            if (date.isNull() || cellDate == date)
            {
                  ui->historiqueTableWidget->showRow(row);
            }
            else
            {
                ui->historiqueTableWidget->hideRow(row);
            }
        }
        if(date == QDate::currentDate())
        {
            ui->historiqueTableWidget->showRow(row);
        }
    }
}

void MainWindow::on_searchInput_4_textChanged(const QString &arg1)
{
    for(int row = 0; row < ui->historiqueTableWidget->rowCount(); ++row)
    {
        bool showRow = false;
        for(int column = 0; column < ui->historiqueTableWidget->columnCount(); ++column)
        {
            QTableWidgetItem *item = ui->historiqueTableWidget->item(row, column);
            if(item && item->text().contains(arg1, Qt::CaseInsensitive))
            {
                showRow = true;
                break;
            }
        }

        if (showRow)
        {
            ui->historiqueTableWidget->showRow(row);
        }
        else
        {
            ui->historiqueTableWidget->hideRow(row);
        }
    }
}
