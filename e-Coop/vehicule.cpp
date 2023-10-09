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

bool Vehicule::ajouter_vehicule(QString num_Matriculation, QString nom, QString contact, int nb_Place ,QString ref_trajet)
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
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Vehicule::modifier_vehicule(QString num_Matriculation, QString nom, QString contact, int nb_Place, QString ref_trajet)
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
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Vehicule::supprimer_vehicule(QString num_Matriculation)
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
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}


