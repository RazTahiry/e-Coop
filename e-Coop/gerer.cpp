#include "gerer.h"
#include "dbmanager.h"
#include "reservation.h"
#include "trajets.h"
#include "vehicule.h"
#include "ui_gerer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMap>
#include <QList>
#include <QPair>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <QTime>

Gerer::Gerer()
{
}

Gerer::Gerer(QString num_Matriculation, QString ref_trajet) : _id(num_Matriculation), _trj(ref_trajet)
{

}

void Gerer::setHeure(const QTime &heure)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.prepare("INSERT INTO VEHICULE(heure) VALUES(:heure)");
        query.bindValue(":heure", heure);
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}

void Gerer::gere()
{

    //-----test heure----------------------------------------------------
        std::time_t now = std::time(nullptr);
        std::tm tm_now = *std::localtime(&now);

        // Affichez la date et l'heure actuelles
        qDebug() << "Date et heure actuelles : ";
        qDebug() << tm_now.tm_year + 1900 << "-" << tm_now.tm_mon + 1 << "-" << tm_now.tm_mday << " ";
        qDebug() << tm_now.tm_hour << ":" << tm_now.tm_min << ":" << tm_now.tm_sec;
    //------------------------------------------------------------------

    // maka refTrajet sy numMat any anaty vehicule
    DbManager db(pathToDB);
    QSqlQuery query;

    QSqlQuery selectQuery("SELECT numMat, refTrajet, heure FROM VEHICULE");
    QSqlQuery trajetQuery("SELECT refTrajet, heureMatin, heureSoir, NbVehiculeParJour, DecalageVoyage FROM TRAJET");

    QList<Gerer> Vehicule;

    //mampiditra vehicule anaty methode
    while (selectQuery.next())
    {
        QString _id = selectQuery.value(0).toString();
        QString _trj = selectQuery.value(1).toString();
        Vehicule << Gerer(_id, _trj);
    }

    //mamorona groupe trajet de mampiditra vehicule ao
    QMap<QString, QList<Gerer>> Trajets;

    foreach(const Gerer &Vehicules, Vehicule)
    {
        Trajets[Vehicules._trj].append(Vehicules);
    }
    qSort(Vehicule.begin(), Vehicule.end(), [](const Gerer &v1, const Gerer &v2) -> bool { return v1._trj < v2._trj;});
    //-------------------------------------------------------------------

    QMap<QString, QList<QTime>> heures;

    foreach(const QString &_trj, Trajets.keys())
    {
        DbManager db(pathToDB);

        QSqlQuery query;
        query.prepare("SELECT heureMatin, heureSoir FROM TRAJET");
        query.exec();
        QList<QTime> heurePourTrajet;

        if(query.next())
        {
            _heure = query.value(0).toTime();
            _heure1 =query.value(1).toTime();
            heurePourTrajet << _heure << _heure1;
        }
        heures[_trj] = heurePourTrajet;
    }

    // manambotra aller retour
    QMap<QString, QPair<Gerer, Gerer>> Trajet;

    foreach(const QString &_trj, Trajets.keys())
    {
        QList<Gerer> vehiclesForTrajet = Trajets[_trj];

        bool isAller = true;

        for (int i = 0; i < vehiclesForTrajet.size(); ++i)
        {
            if (isAller)
            {
                Trajet[_trj].first = vehiclesForTrajet[i];
                //Trajet[_trj].first.setHeure(heures[_trj]);
            }
            else
            {
                Trajet[_trj].second = vehiclesForTrajet[i];
                //Trajet[_trj].second.setHeure(heures[_trj]);
            }

            Trajet[_trj].first.setHeure(heures[_trj][0]);
            Trajet[_trj].second.setHeure(heures[_trj][1]);

            isAller = !isAller;
        }

        qDebug() << "Paires de véhicules (aller-retour) triées par trajet : ";

        foreach (const QString &_trj, Trajet.keys())
        {
            int taille;

            taille = Trajets[_trj].size();
            QPair<Gerer, Gerer> pair = Trajet[_trj];
            qDebug() << "Trajet : " << _trj;

            for (int i = 0; i < taille; i++)

            {
                //if(i % 2 == 0)
                //{
                QString role = (i % 2 == 0) ? "aller" : "retour";
                qDebug() << "Véhicule " << role << ":" << Trajets[_trj][i]._id << "Heure Matin: " << heures[_trj][0].toString("hh:mm") << "Heure Soir: " << heures[_trj][1].toString("hh:mm")  << "Date: " << tm_now.tm_year + 1900 << "-" << tm_now.tm_mon + 1 << "-" << tm_now.tm_mday;
                // qDebug() << "Véhicule aller: " << Trajets[_trj][i]._id; //<< "Heure: " << heures[_trj].toString("hh:mm") << "Date: " << tm_now.tm_year + 1900 << "-" << tm_now.tm_mon + 1 << "-" << tm_now.tm_mday;
                //}

                /* if(i % 2 != 0)
                {
                    qDebug() << "Véhicule retour: " << Trajets[_trj][i+1]._id; //<< "Heure: " << heures[_trj].toString("hh:mm") << "Date: " << tm_now.tm_year + 1900 << "-" << tm_now.tm_mon + 1 << "-" << tm_now.tm_mday;
                }*/
             }
        }
    }
}
