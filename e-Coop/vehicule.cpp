#include "vehicule.h"
#include "dbmanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Vehicule::Vehicule()
{
    this->_num_Matriculation = "";
    this->_nb_Place = 0;
}

Vehicule::Vehicule(QString num_Matriculation, QString nom, QString contact, QString ref_trajet,
                   QString lieu_depart, QString destination, QString heureMatin, QString heureSoir, int nb_Place, int decalage):
    Identificateur(nom, contact),
    Trajets(ref_trajet, lieu_depart, destination, heureMatin, heureSoir, decalage)
{
    this->_num_Matriculation = num_Matriculation;
    this->_nb_Place = nb_Place;
}

void Vehicule::ajouter_vehicule(QString num_Matriculation, QString nom, QString contact, int nb_Place ,QString ref_trajet)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.prepare("INSERT INTO VEHICULE (numMAT, chauffeur, contactChauffeur, nbPlace, refTrajet) "
                      "VALUES (:numMAT, :chauffeur, :contactChauffeur, :nbPlace, :ref_trajet)");
        query.bindValue(":numMAT", num_Matriculation);
        query.bindValue(":chauffeur", nom);
        query.bindValue(":contactChauffeur", contact);
        query.bindValue(":nbPlace", nb_Place);
        query.bindValue(":ref_trajet", ref_trajet);

        if(query.exec())
        {
            qDebug() << "data added.";
        }
        else
        {
            qDebug() << "data not added: " << query.lastError();
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}

void Vehicule::modifier_vehicule(QString num_Matriculation, QString nom, QString contact, int nb_Place, QString ref_trajet)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.prepare("UPDATE VEHICULE SET chauffeur = :chauffeur, contactChauffeur = :contact, nbPlace = :nbPlace, refTrajet = :refTrajet WHERE numMAT = :numMAT");
        query.bindValue(":chauffeur", nom);
        query.bindValue(":contact", contact);
        query.bindValue(":nbPlace", nb_Place);
        query.bindValue(":refTrajet", ref_trajet);
        query.bindValue(":numMAT", num_Matriculation);

        if(query.exec())
        {
            qDebug() << "Véhicule à jour.";
        }
        else
        {
            qDebug() << "Can't update Véhicule: " << query.lastError();
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}

void Vehicule::supprimer_vehicule(QString num_Matriculation)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.prepare("DELETE FROM VEHICULE WHERE numMAT = :numMat");
        query.bindValue(":numMat", num_Matriculation);

        if(query.exec())
        {
            qDebug() << "Véhicule supprimé.";
        }
        else
        {
            qDebug() << "Can't delete Véhicule: " << query.lastError();
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}

void Vehicule::setHeure(QString num_Matriculation, QString heure_depart)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.prepare("UPDATE VEHICULE SET heure = :heure WHERE numMAT = :numMAT");
        query.bindValue(":heure", heure_depart);
        query.bindValue(":numMAT", num_Matriculation);
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}


