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

Vehicule::Vehicule(QString num_Matriculation, QString nom, QString contact, int nb_Place):
    Identificateur(nom, contact)
{
    this->_num_Matriculation = num_Matriculation;
    this->_nb_Place = nb_Place;
}

void Vehicule::ajouter_vehicule(QString num_Matriculation, QString nom, QString contact, int nb_Place)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.prepare("INSERT INTO VEHICULE (numMAT, chauffeur, contactChauffeur, nbPlace) "
                      "VALUES (:numMAT, :chauffeur, :contactChauffeur, :nbPlace)");
        query.bindValue(":numMAT", num_Matriculation);
        query.bindValue(":chauffeur", nom);
        query.bindValue(":contactChauffeur", contact);
        query.bindValue(":nbPlace", nb_Place);

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

void Vehicule::modifier_vehicule(QString nom, QString contact, QString num_Matriculation, int nb_Place)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        if(query.exec("UPDATE VEHICULE SET chauffeur = '"+nom+"', contactChauffeur = '"+contact+"', nbPlace = '"+nb_Place+"' "
                      "WHERE numMAT = '"+num_Matriculation+"'"))
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
        if(query.exec("DELETE FROM VEHICULE WHERE numMAT = '"+num_Matriculation+"'"))
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


