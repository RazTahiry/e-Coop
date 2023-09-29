#include "trajets.h"
#include "dbmanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Trajets::Trajets() : _ref_trajet(""), _lieu_depart(""), _destination(""), _heure_depart("")
{
}

Trajets::Trajets(QString ref_trajet, QString lieu_depart, QString destination, QString heure_depart) :
    _ref_trajet(ref_trajet), _lieu_depart(lieu_depart), _destination(destination), _heure_depart(heure_depart)
{
}

void Trajets::ajout_trajet(QString ref_trajet, QString lieu_depart, QString destination, QString heure_depart)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.prepare("INSERT INTO TRAJET (refTrajet, lieuDepart, destination, heure) "
                      "VALUES (:refTrajet, :lieuDepart, :destination, :heure)");
        query.bindValue(":refTrajet", ref_trajet);
        query.bindValue(":lieuDepart", lieu_depart);
        query.bindValue(":destination", destination);
        query.bindValue(":heure", heure_depart);

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

void Trajets::maj_trajet(QString ref_trajet, QString lieu_depart, QString destination, QString heure_depart)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        if(query.exec("UPDATE TRAJET SET lieuDepart = '"+lieu_depart+"', destination = '"+destination+"', heure = '"+heure_depart+"' "
                      "WHERE refTrajet = '"+ref_trajet+"'"))
        {
            qDebug() << "Trajet à jour.";
        }
        else
        {
            qDebug() << "Can't update Trajet: " << query.lastError();
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}

void Trajets::supprimer_trajet(QString ref_trajet)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        if(query.exec("DELETE FROM TRAJET WHERE refTrajet = '"+ref_trajet+"'"))
        {
            qDebug() << "Trajet supprimé.";
        }
        else
        {
            qDebug() << "Can't delete Trajet: " << query.lastError();
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}
